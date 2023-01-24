// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENVIRONMENT_ITERATOR_VP_2004_05_14
#define BOOST_ENVIRONMENT_ITERATOR_VP_2004_05_14

#include "eof_iterator.hpp"

#include <utility>
#include <string>
#include <cassert>

namespace boost {

    class environment_iterator 
        : public eof_iterator<environment_iterator, 
                              std::pair<std::string, std::string> >
    {
    public:
        environment_iterator(char** environment)
        : m_environment(environment)
        {
            get();
        }
        
        environment_iterator()
        {
            found_eof();
        }
        
        void get()
        {
            if (*m_environment == 0)
                found_eof();
            else {
                std::string s(*m_environment);
                std::string::size_type n = s.find('=');
                assert(n != s.npos);
                value().first = s.substr(0, n);
                value().second = s.substr(n+1);
                
                ++m_environment;
            }
        }
        
    private:
        char** m_environment;
    };
}
#endif

/* environment_iterator.hpp
Z5bWpyfdmll9vRd2u0K0P67spgrCYtJFa/MSFmfEbVQGLeDt1B7M1RGnX+Z41CMGo7KoBN5ppWcrX6s43X/y8tUFxdfhtkrTW/Hp2i6HpAY0GU52n0vSTwiBGqrKup8qN7tUwJTjrjczRhYq6lRlrrEucm8f3Dx8vGcbymIOsumHi0ZmSEuTqOPK3EVsj7P2QDXrVOr5HFhEb/3/6DHnWarVBjPSaqUY5I00BDoyrd2xbFck8JJFCmkMJDToV3StyVTbvI5k90XYHdj7HAF/ecbYIMN2VbrKhhP72ybZ7n0fyT6+VpYcMFuHj7tyBb/6nJI4X0HrWNc8a+L9REgP0CEjlBFFTk03UiBG8+0VnOCEh/KN2u16R5Tch6IZ87o6JnwXbTHh2zPa1QL9MtetkhTj3bKlc3/qorwtqMuFFbpKxmkk1OGp1xobm1A1FP5mNud8nKZXH0rcNuoW456TW65M0W1ee7kUSobPcyKu1AA/j2wiEk/+eiIW1SDLPuz/9owj3uB7xwY3kwv0OHlbX8HV3KAJ9Kn961L+WPeN0iAXG0SDwVMhOoj99zY75ph06OfSI74gQ/OrX16/x+6Mq2CcmhaS5E5tTlwlhQ4NYxxDZzHjOmNx7A8uGeRWq76yxEqgJz5eyjB/QH9unBm567hHt9kVyTIlvp6N952WSk+4IBPxH9/U+A016C38YvKcA5zWm9FdQsmVGsSY
*/