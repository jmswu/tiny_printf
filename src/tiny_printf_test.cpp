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

        auto getData(void)
        {
            return array.data();
        }

        auto getLen(void)
        {
            return index;
        }

        void clear()
        {
            array.fill(0);
            index = 0;
        }

        void print()
        {
            std::printf("[");
            for(auto & elem: array)
            {
                std::printf("%c", elem);
            }
            std::printf("]");
            std::printf("\n");
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

    TEST_F(TinyPrintfTest, test_print_char_loop_all_chars)
    {
        for(uint8_t c = 0; c <= 127; c++)
        {
            printBuff.clear();
            tiny_printf("%c", (char)c);
            ASSERT_EQ(printBuff.get(0), (char)c);
            ASSERT_EQ(printBuff.get(1), 0);
        }
    }


    TEST_F(TinyPrintfTest, test_print_char_loop_all_chars_with_string_at_the_front)
    {
        for(uint8_t c = 0; c <= 127; c++)
        {
            printBuff.clear();
            tiny_printf("hello %c", (char)c);
            size_t i = 0;
            ASSERT_EQ(printBuff.get(i++), 'h');
            ASSERT_EQ(printBuff.get(i++), 'e');
            ASSERT_EQ(printBuff.get(i++), 'l');
            ASSERT_EQ(printBuff.get(i++), 'l');
            ASSERT_EQ(printBuff.get(i++), 'o');
            ASSERT_EQ(printBuff.get(i++), ' ');
            ASSERT_EQ(printBuff.get(i++), (char)c);
            ASSERT_EQ(printBuff.get(i++), 0);
        }
    }

    TEST_F(TinyPrintfTest, test_print_char_loop_all_chars_with_string_at_the_back)
    {
        for(uint8_t c = 0; c <= 127; c++)
        {
            printBuff.clear();
            tiny_printf("%chi", (char)c);
            size_t i = 0;
            ASSERT_EQ(printBuff.get(i++), (char)c);
            ASSERT_EQ(printBuff.get(i++), 'h');
            ASSERT_EQ(printBuff.get(i++), 'i');
            ASSERT_EQ(printBuff.get(i++), 0);
        }
    }

    TEST_F(TinyPrintfTest, test_print_char_loop_all_chars_with_string_at_the_front_and_back)
    {
        for(uint8_t c = 0; c <= 127; c++)
        {
            printBuff.clear();
            tiny_printf("oh%chi", (char)c);
            size_t i = 0;
            ASSERT_EQ(printBuff.get(i++), 'o');
            ASSERT_EQ(printBuff.get(i++), 'h');
            ASSERT_EQ(printBuff.get(i++), (char)c);
            ASSERT_EQ(printBuff.get(i++), 'h');
            ASSERT_EQ(printBuff.get(i++), 'i');
            ASSERT_EQ(printBuff.get(i++), 0);
        }
    }

    TEST_F(TinyPrintfTest, test_print_string)
    {
        printBuff.clear();
        const char *pData = "Hello!";
        tiny_printf("%s", pData);
        ASSERT_EQ(0, memcmp(pData, printBuff.getData(), printBuff.getLen()));
    }

    TEST_F(TinyPrintfTest, test_print_string_with_string_at_front)
    {
        printBuff.clear();
        const char *pData = "Hello!";
        const char *pDataExptected = "front Hello!";
        tiny_printf("front %s", pData);
        ASSERT_EQ(0, memcmp(pDataExptected, printBuff.getData(), printBuff.getLen()));
    }

    TEST_F(TinyPrintfTest, test_print_string_with_string_at_back)
    {
        printBuff.clear();
        const char *pData = "Hello!";
        const char *pDataExptected = "Hello! back";
        tiny_printf("%s back", pData);
        ASSERT_EQ(0, memcmp(pDataExptected, printBuff.getData(), printBuff.getLen()));
    }    
}