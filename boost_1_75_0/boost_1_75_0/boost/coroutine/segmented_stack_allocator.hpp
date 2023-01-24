
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if defined(BOOST_WINDOWS)
#  error "segmented stacks are not supported by Windows"
# else
#  include <boost/coroutine/posix/segmented_stack_allocator.hpp>
# endif
#endif

/* segmented_stack_allocator.hpp
5aK9a4+52ayD6wrn37L1sa49MozVsNc/yBa0yk4v0wVhXXsiAw/3NAI6ZQY+AUZFrrQV5pPHGM5VYrQyIfy1edajv2EsMfLZ9a4S5LVjEg+VIhuGPMg/oDVTPIGXJIHxNDFAAQkHS/zWVvSH1FdaZ8HmfV+huaS9hUwcXHn64FyaIFGOUWGtRYrhvB6xWZHjIiEDxgynOGE+lyLl96ZhMkabhb8GG1RIBLgnz9SQfGRNDcMN7bSWGsUHyW3bhTmJTn/nuyqD4mqyaPDwIYMTPCyQBA/uEIK7Q/DgITiDBCe4u7tLcHcGksHdncEdBhhg8Fl2a2trf+zue/VenT63+96+t6ur++BjsbPNZIBjxGuUSk5bzokQPMcoEkmWlxltzdY5OH14lXKs+qW1u0CM61vhJjTxhLcSHyUdrz2IaQjr7ucxeTHxxHTD1iZiSFqfTWI/K294YdkVengrXrZu55o0KrV2Rr25+sD7CNW8pQ4uEzxMobxSEPgk+Lj7NX84/m6elNg3zjjMFcUv8IxPudwr69SjB76StH4fATPUCEE3IFvmOCA6AOXoZEEzOF2khuOEJSQRu8Zqtx8egpyMfaX2/bIPsXWd3SS443GT9g+wBdXaxabyD11cDxrkurwBflQS3oAOqySoU3/z5OYJ2i9Wv0BNeJixX+QRw0VEBDOZibQC1ukAcj16rr7Zbz+31or+pc0GnnHcFrG9
*/