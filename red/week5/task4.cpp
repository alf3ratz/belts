#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
//    vector<Sentence<Token>> res(0);
//    Sentence<Token> sentence(0);
//    auto it = tokens.begin();
//    for(int i = 0; i < tokens.size(); ++i){
//        if(tokens[i].IsEndSentencePunctuation()){
//            sentence.push_back(move(tokens[i]));
//            res.push_back(move(sentence));
//            sentence.clear();//Sentence<Token>(0);
//        }else{
//            sentence.push_back(move(tokens[i]));
//        }
//    }
//
//    if(!sentence.empty())
//        res.push_back(move(sentence));
//    return res;
    vector<Sentence<Token>> res;
    Sentence<Token> sentence(0);
    bool is_end = false;

    for (int i = 0; i < tokens.size(); ++i) {
        if (is_end && !tokens[i].IsEndSentencePunctuation()){
            res.push_back(move(sentence));
            sentence.clear(); //= Sentence<Token>(0);
        }

        is_end = tokens[i].IsEndSentencePunctuation();
        sentence.push_back(move(tokens[i]));
    }

    res.push_back(move(sentence));
    return res;
}


struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                        })
    );

    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                        })
    );

    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                                {{"Without"}, {"copies"}, {".", true}},
                                        })
    );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}