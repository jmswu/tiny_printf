#include <cstdio>
#include <array>
#include "gtest/gtest.h"
#include "tiny_printf.h"

class PrintBuff
{
    public:
        PrintBuff()
        {
            clear();
        }
        ~PrintBuff(){}

        void add(const char oneChar)
        {
            array.at(index++) = oneChar;
        }

        auto get(const size_t index)
        {
            return array.at(index);
        }

        void clear()
        {
            array.fill(0);
            index = 0;
        }

    private:
        std::array<char, 2048> array;
        size_t index = 0;
};

PrintBuff printBuff;


void tiny_putc(const char c)
{
    printBuff.add(c);
}

namespace
{
    class TinyPrintfTest: public testing::Test
    {
        public:
        private:
        protected:
            TinyPrintfTest(){}
            virtual ~TinyPrintfTest(){}
            virtual void SetUp(){}
            virtual void TearDown(){}
    };

    TEST_F(TinyPrintfTest, test_1)
    {
        ASSERT_TRUE(1);
    }

    TEST_F(TinyPrintfTest, test_print_char_1)
    {
        printBuff.clear();
        tiny_printf("%c", 'c');
        ASSERT_EQ(printBuff.get(0), 'c');
        ASSERT_EQ(printBuff.get(1), 0);
    }

    TEST_F(TinyPrintfTest, test_print_char_loop_lower_case)
    {
        for(char c = 'a'; c <= 'z'; c++)
        {
            printBuff.clear();
            tiny_printf("%c", c);
            ASSERT_EQ(printBuff.get(0), c);
            ASSERT_EQ(printBuff.get(1), 0);
        }
    }
}