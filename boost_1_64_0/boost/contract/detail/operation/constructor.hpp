
#ifndef BOOST_CONTRACT_DETAIL_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_DETAIL_CONSTRUCTOR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_inv.hpp>
#include <boost/contract/detail/none.hpp>
#include <boost/contract/detail/exception.hpp>
#if     !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && ( \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS))
    #include <boost/contract/detail/checking.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// Ctor subcontracting impl via C++ obj construction mechanism.
template<class C> // Non-copyable base.
class constructor : public cond_inv</* VR = */ none, C> {
public:
    explicit constructor(C* obj) : cond_inv</* VR = */ none, C>(
            boost::contract::from_constructor, obj) {}

private:
    #if     !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_OLDS)
        void init() /* override */ {
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
            #endif

            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                {
                    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                        checking k;
                    #endif
                    this->check_entry_static_inv();
                    // No object before ctor body so check only static inv at
                    // entry. Ctor pre checked by constructor_precondition.
                }
            #endif
            #ifndef BOOST_CONTRACT_NO_OLDS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~constructor() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
                checking k;
            #endif

            // If ctor body threw, no obj so check only static inv. Otherwise,
            // obj constructed so check static inv, non-static inv, and post.
            if(uncaught_exception()) {
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_exit_static_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    this->check_except();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_exit_all_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    this->check_post(none());
                #endif
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard


/* constructor.hpp
z5kJvz4K75SDx97k/6vYvVbYylpHmYPzwXvghGf6E9e8zSImhD1G5kqJBbYbi3w/LH1i5uF75LEGsQDWALomEqtMAofAU2eMhBaV6NcW6Lxh0BKadGLuvPTpg+eEilGWoDMH4veuRs9+R59nzWIMl2Lz0V0730cem9CHOpSHj+d1JL48nTgo/NsnxSYGQmwOjFiWSbyFWPI2qb/Bk8U3MB/Twffp2EjBmND3qHCRj0y+x5xVgK1zrsTnpn9nLZeBTtbd3gTr3OERreGjC1biu8zE/5qN3/wCunEO+IqYec4PxDTfJKYCRqmD/mhZC7sXj1yAx1s+y5orZf7endjVDdi4BeCiofAGdmYCsQQfdFiHf5q2lDDLHvx/aJpLcK7ZA8gT8vxSJHolDVzRGHlGzr8II+6HDhibjL8D335xAfqefve5FTvKOLZDw6veRYd3BnefQtwWbFUDPZx1ITYDfl0KvTvQfuab4ODN+LJd6Qt26Tzs8pAG7EmAjycTT0+DLgeQsfuxkxEl/ljmCOgaAS2ykM0Z2I1N4+A/ZKPlGPQx9uZV4kKrhlhqrXcw8eva+OTrezEWfKUM6ilA9vZK3VuKfSzFbq9nHp9FZ0xiXZWxD+gFP2LDmjelffTsg0eZD3DwqAhwP3j3/Uj8F+JgnRb78dVs4raHiDu1GAqd6O90/PJCyn2Zhx2dR7nG+GvEx65h7s9ZA35nDhNSmVP8zQH0vVYz4sPL8dnXoR+HMP+jwCcFwNp04m6JyCK2DlMvGoDr+z8KT4ThX/jAk3uh3TXoq4/QKcQwL7sWGrRGf2wH13fHv17InBKfbAquiwWLeJszthrEHiLYDwJ2ToLW16RgK7F/yWOxvV9hl2r78fMh5HfERfAmOHp1F9byLsauM8Y+0KqonHhbOvPbkL5cjHxiH95g/u8C090Ri999HbIwiO/DnUd82Me6JnJ3G3P7wjb46i/oQfDdB7XRq9/Tb+RwAzqoTRkmCp/l6w3MSQ/WouCbAX2hOdjidPRNl0XEw8cTe36SuVtE7GIdMWViAQ3ysf1g+gt+Qpfw326AjWd/zZReYEsf8vsQ5Virp4vi9MnwPzT8Gd31AZi11dPwKeXbfItcIjML0D356I735fpbF8YNll61h9jF5dh2xnQm81S2BLsMhvz0KHVInEI/lnZinPORZ3RtKr5I7jmsla1kvasvMoTt6/AG4xQyPo2+/Ab/YiN6sgnxrbrYxS34lZdBX+avS5hHHMFH7HYAHI4+/Sv4uQdYOukjfKOVxLUXo2vbYDv2Mlcf4qOtQi8x/muZ315r0KsN8evA5tORn69WgGGJjTXKwNbPxL9/D6zIe89sIW6/A7psg65gxPuX0w7+Sc6rxJvXgmMWYOfK8W3mWMiyIH4JPorBjn1H3/BXOuLL33MRWA27lI3OiNlAO18y5lXE6N7Fhwc3xUzEz38RO8G8rv0E/fI0fYtGZyZj88GkvT9hzagxtge/u357/D9kN+wS/qNzisAp+24A84NLx/wAfZnjZcQ0u+0Da/dF7+0gJjwa/JeJPk1krwm6ox74fhl+54PXUj+67qG1HpHswU9jbAP2y29vg/3Ad7N5ZwtrLTezvlYAntpxEL3TDJuWQAwJPyH3HmSPetpg73a9DiaCDw8Pxj+G7/qA48/qTuwDPLUnGduSAbaKYd0Mm3AwBx/hYmIg6OOf94PDIsHDE8FPHaE7uDdlAmsJ+E41bOiKj3gdsb3YYexdqoTPjhJvpe2L19PvqxkXuKRmBfoOmRywFzx4FmsUYIl6vYjTnQn+QAdFvE6/0R9iIHLWGt0xH73CPKSDNcufECpOsjZV7g0D25Qjy+Cc3Vfa4gw=
*/