#include <cstdio>
#include "gtest/gtest.h"
#include "tiny_printf.h"

void tiny_putc(const char c)
{
    std::printf("%c", c);
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
            virtual void SetUp()
            {

            }
            virtual void TearDown()
            {

            }
    };

    TEST_F(TinyPrintfTest, test_1)
    {
        ASSERT_TRUE(1);
    }
}