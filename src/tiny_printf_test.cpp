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
        ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
    }

    TEST_F(TinyPrintfTest, test_print_char_loop_all_chars)
    {
        for(uint8_t c = 0; c <= 127; c++)
        {
            printBuff.clear();
            tiny_printf("%c", (char)c);
            ASSERT_EQ(printBuff.get(0), (char)c);
            ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
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
            ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
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
            ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
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
            ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
        }
    }

    TEST_F(TinyPrintfTest, test_print_string)
    {
        printBuff.clear();
        const char *pData = "Hello!";
        tiny_printf("%s", pData);
        ASSERT_EQ(0, memcmp(pData, printBuff.getData(), printBuff.getLen()));
        ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
    }

    TEST_F(TinyPrintfTest, test_print_string_with_string_at_front)
    {
        printBuff.clear();
        const char *pData = "Hello!";
        const char *pDataExptected = "front Hello!";
        tiny_printf("front %s", pData);
        ASSERT_EQ(0, memcmp(pDataExptected, printBuff.getData(), printBuff.getLen()));
        ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
    }

    TEST_F(TinyPrintfTest, test_print_string_with_string_at_back)
    {
        printBuff.clear();
        const char *pData = "Hello!";
        const char *pDataExptected = "Hello! back";
        tiny_printf("%s back", pData);
        ASSERT_EQ(0, memcmp(pDataExptected, printBuff.getData(), printBuff.getLen()));
        ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
    }    

    TEST_F(TinyPrintfTest, test_print_string_with_string_at_front_and_back)
    {
        printBuff.clear();
        const char *pData = "Hello!";
        const char *pDataExptected = "front Hello! back";
        tiny_printf("front %s back", pData);
        ASSERT_EQ(0, memcmp(pDataExptected, printBuff.getData(), printBuff.getLen()));
        ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
    }    

    TEST_F(TinyPrintfTest, test_print_16bit_int)
    {
        printBuff.clear();
        tiny_printf("%i", -1);
        ASSERT_EQ(printBuff.get(0), '-');
        ASSERT_EQ(printBuff.get(1), '1');
        ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
    }  

    TEST_F(TinyPrintfTest, test_print_16bit_int_loop_full_range)
    {
        for(int i = -32768; i <= 32767; i++)
        {
            printBuff.clear();
            tiny_printf("%i", i);
            char buff[64];
            sprintf(buff,"%d", i);
            ASSERT_EQ(0, memcmp(buff, printBuff.getData(), strlen(buff)));
            ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
        }
    }  

    TEST_F(TinyPrintfTest, test_print_unsigned)
    {
        for(unsigned i = 0; i < 65536; i++)
        {
            printBuff.clear();
            tiny_printf("%u", i);
            char buff[64];
            sprintf(buff,"%d", i);
            ASSERT_EQ(0, memcmp(buff, printBuff.getData(), strlen(buff)));
            ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
        }
    }

    TEST_F(TinyPrintfTest, test_print_32bit_int_edge_case)
    {
        const int test_data[] ={-2'147'483'648, -2'147'483'647, -1, 0, 1, 2'147'483'646, 2'147'483'647};
        const int counts = sizeof(test_data) / sizeof(test_data[0]);
        for(int i = 0; i < counts; i++)
        {
            printBuff.clear();
            tiny_printf("%l", test_data[i]);
            char buff[64];
            sprintf(buff,"%d", test_data[i]);
            ASSERT_EQ(0, memcmp(buff, printBuff.getData(), strlen(buff)));
            ASSERT_EQ(0, printBuff.get(printBuff.getLen()));
        }
    } 
}