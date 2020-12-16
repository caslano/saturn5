
#ifndef BOOST_CONTRACT_DETAIL_NAME_HPP_
#define BOOST_CONTRACT_DETAIL_NAME_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/config.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

// NOTE: Explicitly list number of names to concatenate using ..._NAME-n
// (instead of using ..._SEQ_CAT or similar) for optimal speed and reentrancy.

#define BOOST_CONTRACT_DETAIL_NAME1(name1) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_PREFIX, name1)

#define BOOST_CONTRACT_DETAIL_NAME2(name1, name2) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_PREFIX, BOOST_PP_CAT(name1, \
            BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_INFIX, name2)))
       
#endif // #include guard


/* name.hpp
pamlsZNH/Shwu9e1NOta6NfaXqd0MI/KHqvv9PGcq3XxGGKpfv+tvgWUV+J1cEyGk6PbMnuQd8L8XOTxbpKsyjraQLt3BXljybUFQg7Ab3ttRwvyq3nKr77P6dtvw8mz2tef2dIrd/NWOr3aEU6QZk1FE3yXrVN4XgQ8l/yP8laZzWFqkfUNchcuGwd+mPPQh7EE6i8YY1ubRpETy5N282sg3GggROz8cpmzVwrvm3z5bUmeRX6MFHkxook2tyApbDLDOhLxzZy9R9tL8fe3uNzubcPst9H8aZTfxDf6NI/f9Heo3CGKW0F8lHqJDRkA4JcRDRpnXXTHnds+ieRWiWPNth2GWgCA18fg9yp4ZJqBKmX0jqDIa35OXw+GN8QinqbzPIobQEfQXNuOlX5eDvxO9tzgJ564EvmbalA982fS6c8fs38s6BWiZ1cKD5WjtIGOn3WTE0eaATkSV+FdK7P2Yo3QE93I+7Vx1JCLC/hH+fSDbzG1K33dWCf81MP66crhnr5ReR2HZ/Z6o+vTG0J8iZR40Hk7WfL7YgM5Y6jAvX3Krz8oLo+h5DCbSlm8Updn8Mq8JL0jEWVMzVvE72NEBmIUeyDkwDCOq3z8UJ+MWeV5Bb1HHN+YHg6RCumP93qKX+P1pgeHBV14PpHa3OwJfXdFOOS/Z6HwBoJ3eA7g5/cObGB6TZS/1tsQTUXIhbiF3tCNb+E3IabQ+FkF42edV++0QX33Wt0KQZr6t+4g9FBWxpGeIbqS21sXS7l2a0ydFtSPY1w72nLe9lhPKgHf9li/RjaNXPdstkwSUboMvDkq+jrNcygcozlfS6JxvLD9d7KZQ7yA0NTpooeP6pkXk8drSuC6AHeZ++ppZYtFyB7VtaLAWxMeSEc9lcFqqLdU5lfGQcr1mjyno6Vef64MZ956mct19g+TmpO0jG/Ujy6dJG1HefomSDvy4Pc/tVL7H9KuzWPUTZrH8ZUoJITLWyJtfjfUd5gX6uyqBZWVTbJeDFy3xygnpyO6REd8APkmnV9PQmt0cawo8goPIjOGM3AaODCO98uvZntl2GW3uEfK9Y3xUq/f5XXRhGfalRLzogfaXjYGfRq4Hr8J+2f+uNz260TJ2jBd/L5zW3pwvb7PfRy3rUvfVc8aatQeLbfIa8l5K3rSLKe32uKpumifa7rmNbu82r6U0j6e9VRXzvv0p1DeOs3LmIAs1j1qG14o9fUMxTaloy0cy0VhV2lZBcK4v92LNG5NRYe40VKmm8rcTXZBBiBz4jDqp7XQT/cdYO3uNGPLtzEOqBMlL9ie0RgOp6GOfBN2WKAtMpqOl3nz3pW5vpPTKc16zpx3OwP2UISjcYT5h3uodYDncDDeMOKtl/3OsOwPD4F3Gok+6zw8JxCFNJ8/maP1+LhqW8yxb/OKfRGTdmId9q7IRtNG2kcyPfse96DBGxaclMGLEwzru7TA3F3XfSHAh03csiTl815YcNAPk5a0y0d76SMzua0jjInR9T5/izJjYkYR3KsG3t63Ur8hy75X/p/j/jf3e7dLP3xAaLP8AL80QM47pMyHpAz4Exj34gIoa/wJ50jZDxt/wllGhueCfHXMpfTbntD4mNAwfcX4OEc+sdIb477qwHsLV+8nwSb+FP2t88Dy8SnDx4UGp6wA7W45hw1j08EoH+B0J17a/jmUvc4xL/vLL7Bl873PS9lLAuac+oHPknou1THEcLtfQNyJ3pfMfBo258O+vBLwUVZB41LPaAuvX0VeZf/k6GA86CvQpwU0RxqDVwrtb6AMtUx+9v9NAWW/KWWvlrI4z7A++9b6NVLu26Y9Lxxj7ndQe66DfsPxfoOps6xAZAd9LnI=
*/