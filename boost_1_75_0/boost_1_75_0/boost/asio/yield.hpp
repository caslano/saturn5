//
// yield.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "coroutine.hpp"

#ifndef reenter
# define reenter(c) BOOST_ASIO_CORO_REENTER(c)
#endif

#ifndef yield
# define yield BOOST_ASIO_CORO_YIELD
#endif

#ifndef fork
# define fork BOOST_ASIO_CORO_FORK
#endif

/* yield.hpp
Ci7Kfv79oMp++Hw7uW1tkPX8+CBjPbkhrGdeR9bz6s3/Z9YjrJRl5TAk08yRDdO1/Oa3IL+xYt8N3/5/5TdhZSq/eVbLbzwafhMxVMNvZm5l/CZcw2/MCr+JcOcO41DL6ZzX1F5kTRf/sTVtXaHgS2E0MQqjAe1iGGoXnfOXay8CS98/BsvHyyksMmeB+UNYNncGSwee8reL8BTvH+MpoxksdiChCxjKG4f+Gwyl7t9dMpR//7tzhjJhuWr6TtI6pfB4H00x6dxVvzHS4s1vfPNN0VqP+YatJ5OLB1trB1uP5MKrOlfYvDdEa5XkF617JJ2IaUAqpFNoMNlIM5jJ6d7lBr1fikDD+Rcxf49L5yR3LqSGf1a9iMmvhuFVncCuPhZUc/Tz5xVzFJlWtB6vT2nEmCRM9vfGPHo6F8/Xuf29zYV4qth3B02H9if4oDu/lsv2rgzD/PO1hIc32Xo8slKI13ZLeukMcjJX2HwbmaeAV62Al1Ml5VS8yi2hJuZo8o9DrYHX5adBUk49ABNIhjGT26a30AtGh3IAeDY1eZKbClI4UdjPD1tvlKoKWibz8XNI05t4aKaR9pjtjU1aH1VYKXwPtaQD+jJfYsFKHcePLlgJPHZEwUr9ZGGwu9hgI8U0I3xWtbskXM+g0ZcUpEwWs6r5L6QSKasqsUxf4U7jxKwqMatCOsOPoIMXoZkNfwWuI6k/cOzcF3+L
*/