
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
# include <boost/coroutine/windows/protected_stack_allocator.hpp>
#else
# include <boost/coroutine/posix/protected_stack_allocator.hpp>
#endif

/* protected_stack_allocator.hpp
o4oLs2pAtfLqk7J7q4hkz9tkzolsw4PG+paSPGG3eyjv2QLBvljC8LslJKD86HzMJg4a/jG+FUL+fOn2SMgAiVf4Q5ZXUWot1WYQA1uWXsktcMQKL1QyQjMCQ1otYm4FGls2f+8btiJOn92+DRRu6zu0i6CGwknT6BHW2/bnxFAjhuvHSpkrzqSdQ4deBA5ti0GKCvJQQSi90qf8Hm27ORvfQYogFQVGpSQ2qOAg6Ft+7z/E17xOr6WVyG/7RCMMIuCkZqRR90gpVus7Iz5dMQ4F7bbhJPLa5545xpU2j7D9dU7YTKPjMc45OKNFRSo+nRtCIeM9cD3xXdbP74Wzu3nCnDpDFc942cVYTojUWhJfHp4w4W1j4DGrDP8RHNe99rgz55/Y9A8MYvx/EfAPvKL5B/7+By4x3SJ27RZD5Fn+NwLlr/mhQKH39MGRK4ykyPfbdue00CYGfpETITw/FGB/zkOq2fkFc+9OCWvQ4vXEDnlOMKZ+BuaFm8mVy5H7wbdbxLioegc7iWbfx5xa6KAzY+ZVT4wDyK6OHc8ol2ZylTplCNCSJyO2h/+F1TIdA4cBpEjrrie7Pgy3LBfGrteUp7c8ONW+JWfS7DuV2QdqOMt9jN/ccF1ewPzV3Sa7WcA4Cre9/b/bLA7/PNo8CI1E0USwiuCZI6jAD3JInSK+X3iPLcrH1B/1/NJ74M8vUqn0NdF7h+hPllVm
*/