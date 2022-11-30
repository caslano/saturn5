
#ifndef BOOST_CONTRACT_DETAIL_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_DETAIL_PUBLIC_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/detail/condition/cond_subcontracting.hpp>
#include <boost/contract/detail/tvariadic.hpp>
#include <boost/contract/detail/exception.hpp>
#if     !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && ( \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS))
    #include <boost/contract/detail/checking.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/config.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

template<
    class O, typename VR, typename F, class C
    BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
    BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(1, BOOST_CONTRACT_MAX_ARGS, Args)
>
class public_function : // Non-copyable base.
    public cond_subcontracting<
        O, VR, F, C
        BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
        BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(1, BOOST_CONTRACT_MAX_ARGS, Args)
    >
{
public:
    explicit public_function(
        boost::contract::virtual_* v, C* obj, VR& r
        BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
        BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z(1,
                BOOST_CONTRACT_MAX_ARGS, Args, &, args)
    ) :
        cond_subcontracting<
            O, VR, F, C
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
            BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(1,
                    BOOST_CONTRACT_MAX_ARGS, Args)
        >(
            boost::contract::from_function, v, obj, r
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
            BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(1,
                    BOOST_CONTRACT_MAX_ARGS, args)
        )
    {}

private:
    #if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        void init() /* override */ {
            #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                    !defined(BOOST_CONTRACT_NO_EXCEPTS)
                this->init_subcontracted_old();
            #endif
            if(!this->base_call()) {
                #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                    if(checking::already()) return;
                #endif
                { // Acquire checking guard.
                    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                        checking k;
                    #endif
                    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                        this->check_subcontracted_entry_inv();
                    #endif
                    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                        #ifndef \
  BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                            this->check_subcontracted_pre();
                            } // Release checking guard (after pre check).
                        #else
                            } // Release checking guard (before pre check).
                            this->check_subcontracted_pre();
                        #endif
                    #else
                        } // Release checking guard.
                    #endif
                #ifndef BOOST_CONTRACT_NO_OLDS
                    this->copy_subcontracted_old();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                    this->check_subcontracted_entry_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                    this->check_subcontracted_pre();
                #endif
                #ifndef BOOST_CONTRACT_NO_OLDS
                    this->copy_subcontracted_old();
                #endif
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_subcontracted_exit_inv();
                #endif
                if(uncaught_exception()) {
                    #ifndef BOOST_CONTRACT_NO_EXCEPTS
                        this->check_subcontracted_except();
                    #endif
                } else {
                    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                        this->check_subcontracted_post();
                    #endif
                }
            }
        }
    #endif

public:
    #if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~public_function() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            if(!this->base_call()) {
                #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                    if(checking::already()) return;
                    checking k;
                #endif

                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_subcontracted_exit_inv();
                #endif
                if(uncaught_exception()) {
                    #ifndef BOOST_CONTRACT_NO_EXCEPTS
                        this->check_subcontracted_except();
                    #endif
                } else {
                    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                        this->check_subcontracted_post();
                    #endif
                }
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard


/* public_function.hpp
DlA7shbtlVdS/SemrZDhyvtgmKpLuEqp64W+le9SMRMMtdK9sZRslgOGOz/YU8hBrWDtQhdzUUbh6ffTvYwqeScDFw1ukMxmQoxS9LOPft63ZEagcbL0C/B+poLS22S9K6WuNSBNzqflGihzB9RlJZGhEfhQFkD/UVSSGouweOVwgHhLV8ddZ1Yp+vH3dApJx/3AGkWiv8uHj3Lwzwzjo2ebyOgE+RAZ0LmUIK4CuIlCSOFwSBAAyZn8oRvqfiDrVdxr35cMRoHhdQn3ioEgXoutzaUhhY+5V8msqBFp6EdGd5jkQ43XQCgEDTr9RrA6bZw2XK6gRjQxm/KMeCAGm8C0YtGtgXDX+aTw9C2r1X+uLlOYRLRd+XAMUrXTUYFgQTbrW6LOJJRIZ3HgTeZQelvql5SjWWVDOKGhKSKDc4QYh20kYbXwnZt4m+KwMmS7vqI6+GF0pdOQTutzS77IbbIjJE0l8N6XCPhXYwX/A/WtdCuzvgS4TdJgZluFVKYpOJGVbjqMzijPYiUzxSY8VPVv59B4XUlKTie+gB+IfWE0sgMfUiywN3gRI6vXXjpMvq60wUHQmQ9EAyBmFkkPOh4RoXSHnL9s6lBK/gX6TStXnqSQf05h4Byh2Vwe/vXlhu/hltL7rI8fMxaSP0sWOA69T8bIPw5MSmX8wowi2DBW6IxQYNZ5B+daOXq7NvSRqn540bRmIQMHuNkxvBdr+SeK1Zo36brpmSLchK7z3ijv3HJ6Unu+/oDGYPLCWMaCrMnJEAKR4Raa4kGcJE2XYN+9/jshDsD79kPk2ssvssx0ECffrqUPJrAsoQBd00CFpGSLee1IOLxDNbAmmVSKUm0Gg3+UwkcycLXbcsz0dor3bf9Oykv1XhGqd/jxBaAI5AspxKbLeCsGsCZqbDu8lDRavKX2cV1zkYDUuAt6ABZekbXCKtgCQMKofj83gMRJrCWcZNl0W/Pzq+RNAtPNfEecwekaQQAvpbvzfSEYyq8cezQnBJ9NuSGZ+SzYxxqQwJ0iu3WjlOeNC9JIpG8HZh7MjtC9g4vGpoCJ5O8IMGjnrJUBnK9+ZoRs1EcgaiGJw/g/9WlHuhFIg4ZhfvbGtr24TYdD+5lcf2ifliaPRo38+YlVM/zvT2usORQFhhaaetUH6XSPC/ctEbsl9ilG142EKGc7BPR5tXVdwAA7hziHgBu7hFnVHJwX09K5NtxdM1t3a/EksAO/UTDOKtEOvH0bsxlnOw8X0oRWcE4lr3S+/ZiinvjtC/EXQs7NZHRi1lqi7Uqiw8UnBujre8bilKJyBd82Hq8i7TcfsdVuezTC4IbbfuqUFhLWOb77PKQZZekGCgwyjdK5ps2uF2FyrfMebRse7Ucez+88Okg9O1k8u4Q9X0zVoFAA4j7LKrDgFEjLO37vrMwTWfOTwzMOigVpFSat/1RfEvySuQaN+gKL4Xoh9uInZylMWHYGWvyTexrI3NFr75ukdGsfds99AxynbOBOzqT6idisT8JEYCURIwqU1k/01EnMdYzn4cBappDMpzhNEIMgooAYbDKNYfLfM2X++hG8xwGWsVEDggMgRAl4Y/OquSxNMdy60p770T4HWT7fK3x+tPv8vPzRlPThIEN59mz5KGn/eM+H6/ToN+z4lObYROL4XOv4sGLf4+PRn+BjnOPxr6Tjv0kfQkfrvFeHeIuFX5QIb/8QnZB+oFDmOcO1+FVSz8l32GLDC5Xlxlzcyya9rKzldsa0uIGAUmIPGTah6s7S9ZJv31Z8ens0DJzS2miBINeVMtb6cBtQzw6oE++i2ab0EsNKmTehIoCUSKwBIMaJgFkiLBRpsQQ/A5MDSzXYM+HWzT9CX/Wbpr2a8K4tL4Y3m+WHtJyqyhcK7g/yhLzi3WeUpw6IuDkVe/IEL/GpQFJFUSp2X44kQFIkQPzPqdzjAIknZ7INZ4ovz+QJ0vgep76eY5q8OFPdr1D7lKpOe14OP8+8OlOROddsqMnwDdR6Wanx+Fz/5bkOz/m95ED0k3OamXNd2gvjVe5iPSEoI7Qrr0VRp90EG0t5JkpoLKmp8EKY+ATJ0WkGaKdQiJuUF4vq+Eq2kATYhDDrJCgd4siZvjhtQN0qpQk2EzJtJEmMxWFcXeT6iQDtZY7/ka1HNxLbKRUAR+pv55UoPmn5N0IkW70y49eU5oCPYwBkWJCwBfZezSXht1gKiziDDkCeQSZGntAMTWSITz+7d/+BTxZOlFM3nFOnhA7/JwVeK0uv7lGlS5aW3Bea+S4tM4Qs/mtohmt6zvPUXNe0PDuiJ1epBSphRe8IMwz/ZoT+TXsSlpcclvsptISMqFQ7rEwmrPz13+KQsKp3fwtFwitVrovIruvMr58dh6WzYfUrAc0N1yreBU3Pwwd+57c+v275WtD+Mrz903WbXX6HSEQrz83zT/Am85vOT9c971J6k29e/rkeoI14EXIz1HAz/PLm1eubR1XhMCRWNgeLRAGhjVhZXqygThshBotEN06+bFo6BYnzApFuWCK65iUPABQFnHiMXbK8BbkBpu2SCItvl/ixXr4gcUPAe7t/iGIseR9U3RC7JIKVnG7Aw4pj2a4gk9r8WyJYKp3Yjyp3UzLR37LBe3b/tu3ulvQMamfi7rlFl3Y1EQKAMAxAYiXyu0gUjA70hvUOdBLHNg35r5tdCQEaKnfFxHQRkP99FoN0z//Iyn87EvPla8w8QQrCHUKjY9wBUEuA0RJ5uXWgk0BU3EZ959mMrTEMIhSVOrm4yQx6fO6Pg1yQTgZeq0gxVXxnpphbqZ6Kb9H5bTG9a3SCewAALP/T/v5EmYrf9VCYUePDEs0QClO584MPMWg7+XurL/iNGy3qpHuemn5fbmL8X8hut8enLu//E9ktLVpqjuk7vwNztdI1WU4mbDWb5mHtQbVpeDFbg8qVb68T0+lhBgCxdtNJX+b2RFnfLVyK9mMYdOXDiEQTnsSizfLbz06I4FyFd6y0z1r/47N27zcUhDzhWMauwO8ffq3SzC9EW3sVurzOEaG9eU3XtT8TpWlVrDYKany1vdubFLWneH3+Hb9L4fNmwQ80/dDWyOfZK2jBkO7Wx2LBp1r/3CUpZML+5SP0YVOBuXHBcleoBHK9/yK7lqFsSfQefWzJpEcXbHYRieYGsfgFIDFzC1w9WbQl4Y8DUiSNgEi4vsetJl1i2cLRjr+ZriYt6jevY+heBjWxp25RCE2uhPxnzoLK6cb36fxdcP3ChNhq9iKp65VqUQvlJjw7L0RQVVWIjP2RmYQblHwiIawtjpYPFTeNsnP83PQwNSLoiqcylkietyqRIZy3OlmNz1ZMteCSszZd79olI6foYlyl2W1pNc9jVHc3lDGR4Edjbgn/9yYxs7Rlin2ua/7Wzhl5gbae1XCB9oQxIwetZ6uJs6XhUAHzJucgebPOFGkJwAsPd1+tkn49BaGej5YRQr2fPQa9q7wZZr1eMPTICXu9m5oSGvjePCg8+GvgRnjII1YB1zVb8nGVfm9qUGTk3/WNyH+a6Fn3PMb3ER0vXagd3xA9reQWnSDXVxSbpLYyMB+bkn7h96L47ixdqz0wQQdIaegrNsPXMiQ+K/TACr+Rt+GAHRXZuz1x72K+h0Iz8AzeSiyoEitJvvf29qWpK6iok3inTPtPcumhvpLUhC6ZFc2ikvGw1CebiH9BbWY3embL9+OjpFfdW4aDrR1E7o3OW75QkvkStDbcs+ZSGCXzNermn8xkmCNJyCKWMVp2O9VTQPZzwmyb7E6uvnJYpUO2UOk3F+NXcvvlEUfLHXo/y//u15VGD3x/kl9ot051lSp/2Dl79PJHscjDrp8vfr5SOLYmKD1/pACN+/BzmDFG8ZQfLzzwiI4NTSDzRl9F6YLi06v3OvAd08iLLxF4pZefZutHQzZLY5Sv7ccJhx6NUT5Tvv09i98/NX+yq3h+9nMEr4KnTBupvDxdGgFSdGDd/z7TgqOViek6YkkP7f617yuDfI9jaYYwf9hTaG41yeJZbjGwxbzhX7EdCdyHzKC6LhxlV0fis0XMTa24ItFAR5K0CROilCB9P+gkSfl26+udjBoQ1JmiZWJFRG3xikO8M9Vklu0Rt4Uqj1FnmmA8+yNZt0kh//fOaks6gIaVSbE8coyutT39YuNUqD15hHjkV4ZvvK9P2rLD/qzZ3+01vlZy+JmOh3Owgvmmrcr9UuMVOdkJP04Bh3OTUiM5OaW6dZS3OpNzhzi5+Xa00S5d+RWt+mz0V28e5p1ig7q/WtRazJh2nbLmIwjJrPj0zXzy8Akvhup41FNnbdT885p3uEShf/WEYC+K41u5yDOb5mR/+D+dZ6rZNdQtssoh43w3xE3LQ69kxLlFUYvjli230DZf9RPkt0/gGm+aZ7f0Flr3jRdY5nvHze5rDjd8o3j2dxyvmc2YeFWvDPZQjx7bpohtzEZThqtdlu9SMBTH8lLzv4dpncUsRb7RkPBAe+fVlgI+8upcyNxPchHjOEDw6f35dL9nSKKCL6pJ56PDg8ix7vqDb/uad+6L5RXZlTBN3gfxekp5RZNVSGp+ozDz993WSyW6Uc2HsjP3Hqv1NDcwusvJ+M8HWva0lFm5W1r++NhZf79+vW9fZ7rZbGZr6Rkr3kbAmm1/MV5eqj0YyvTwjcNSykbP8wArfsuSH59GP9xrZuESdHifZOpudMrKc0/QaRS2TDIm0VWkZKX0Tm9x1j/Yw/uju6u6QE8/yLS7ntrS9nXXp8WuYGesUjrGSsCqgL6o+cVw28W07v2psZ3Ovn/eH41KJ2dAL/vIZwUtM1usJZKkGh7bCAduaa4OaL0c+EHRrmXm+eWXy88el1ShkHHPtlVl86E9klKfxMGPZ10y5vlK6RZrAnbWbCEvzoZFWpWtbG9PPxku/hLB/is1/ahc8ByoLJo0ZEVzwt43Ssv+PJ6j9c05ad9L60LRpF+nG3vkMuMsWYZRi9db5IuaI5zKfvjUcUvDgeq+ycoW32Diw236J5qji63cmQGKNPCfxVPpwxvhEa3fSL4+H1c78kvJFnSiFKB/w3/HF1Sa4XB4pz5oxNKZ+XpsUyCm+LX15Un2lucH4phHYxos7fqzis4vuM3f8rh0lerefpUNoZ8yLRIrH32T2RnmZWaSNPuRl2vqQI6qJuyVC4Ex7+aXu5p3pPLOyOn1h4/1rheG1l9o+ewdPLK/ZkdablQsur/JN1v90GdwXr9WVKUkIFSe1v47q181WfLszeL6SVvTS3h66BjfEmeaZGpjAjGgrlCLIWzx52b3Exk2N4726ekufGeaxmBeLh4Je7QJSUd53bBXrYlh7uPp893z4RZrpIs6fUK/ijGDWSTNS6Xipz+9Yjw+qxb3asnWmEJ2BtLfO062X3Gw5uWMldYCoDGvdE3v5vi2Lvh0x/xGMxN+JlKXATNwtK+KMwXqv72TkuWzGGXNyNf41odLdEa1F2fTDH2j+b04o89OPeRbQ0fzMKz8/jyrGRK7/xITOjbyhnXeumxflWdSZXLlMSr6xz0aQzCgmpQAYBDFRNM5sfTifpDu7ThINwe7vIUCqq/DDk1UBj/iyeOa9KN+4iuxDHMVQYR0r0H+2fKAVh9g6zeln3kH05/G7//pSi7/wTOrsbWFCwJN2Jw44V9/AaKAw2c2PwFXCnycfsH4NpEq5TrbcBKOe3kxOuykDO/V1O6qIKq334hJ0DoaRCfZXjl1AD+0DvgVJlfGBHXR/DLlJwcFeSZv5SWSD3309S4pBm532fL4nwomO4doIZoDnqp8OoJDb/BoXOIxwz+9Vf4RUX293n4yfCRlFLui8OzC+jgayp2TuYat/PPhOZoe1Ry48LVjMU8nnkYnjrIAwKgRS7UDIOPEAX1UqSRRnHQYEA5NqhMLDAZBWVBkBhgqUQzYAQNy2gTTbIL1VEG8KChNJbioEiZdCd/DEXDieC0w4JlN3shKKkMMAQMKoYNB6KnyTGChekAyxBZJsBoiS41qCQMy2CSTxlcCuTGkKDZyDSA5ZIv3BEfCskUWPCaN2iQxqqKaQBNmoMEmWM4lQrzYQyQADry1+zmsTuU2QeA1gfLS4M+YZLobR46hQQlqEA8N0K06axaUDIcjKEaDfCaIS3DEpOys11scROwsP7ZIN+z5ObFcd+q8kWhet2qmH/Y8Y2j2JDW26E0txW22Uxy3TzVbcLVW4DbTGFaLyoHtBxvqVSWqa5vgkJ31FMDDDeA0jIXUxrIKxkNNtBlY3t8XVKePHHsE2VaZrmZv32byd5BKqpYycuQJduCPRPPjcDIbWyqH1UynOL67KsEkDtnwGu47B4GZLe5VB8n5Gsl5R95l/LbCzLa05TfZvGrl+ZpHxY5C1458ttW8LLUgIkegGxDM5NjIWUMyqqa1RMi3DsNmOIJ27FlSvmkljMk3O0pu2AvcxssXccregdk9IBxZNYRu1fxjNUztnHol3wSTOGWjd+4V7RAwjd4Lr2XPqtEqrpWtV5OtrpWpV+NFcCkEcxhv1N5r5uBIUuNFVfNmjdFk4K5149S5iTWWc5752kAjVe8dVSsbsAuGb0tX11nWc1m112kxjarg6qynuGzm62yWuWxZVB8d7aqc1NldcmHu6jAwbnsiF96DcXsWFztubgd2bqMxtJGeMy8CRJM3SpsA8DZ5XRDoTKxaquVrA4vEjypofGNqdmB5ta1irc6tVs+tV9fDpMqLq0vA1XsVTZLXjnnvcfsccT/02ZYpwVLdxoIysFyCSfle09e+e7/P00x8y2kigfSBcWwV9Tzh28AJZ16DcS8WoLe/q1c4T0hwQ2j0fmiSq7W/q80Ut80eV8RMXdgrnuB5Z5vtvcgfLj7Se8AD9WgfMHUGmskJK+axp85N95iP5xCna9ttD+1mod4BSFZoeieNSTk1JAwgrGacvVx4vW3j6azVBazBPPVxhDmxECosq2Qt1t85sexpbH1WLJVOmCbq3qvdcCO4dle6gA/EemovyH9f8oAnhJ3LS89ZwGIXjtbAsrgmdeDd0iuyYhtjQU7xDLfxVEvfLKZdqxb2u532tSRHBWwbpJlG/wdpHpXC7aEy3I1KAJyVsSBeNDfdvgtFY7lU0z4VGbg2VisHqOhfnbV8sNDH7lW9E+ShQb2EE85RJ/UdQznxPk1zF2ACkE0AGGRjHTBrZcorz5hzytXuV/Sy0Guo8sxwZi5zVyE8qnF1dLWJTT4aJOegVpYxNqZm0mJcMYsqJdOoJFMsYcdorhk6z6U5UfS7Vt/bXYv7DfMk4nG7tJKNkmaOrbVxwfNEDnfx0ktsZJBxlfOx3juwiNuEMGBM+ATUTzouej7GAlBlzHHlR8Yy6aCZ3FQ7SA/ir/BEtZ/JT9A4ZRSgbt3A/6joI0C/k8VKc9iyy9bg+b94LsFx8fUxwWv3LG49SwaiJ/dbtGq/q8jitM7VJN0gkrfxQrfq7IAxlco4oTJBEfS48OGY6MoYcOeHZLdAqjBnGj9fiuma0ZefAkNxWhpxldQ/SxMY5BJLhmkOXzIfvjtPGyOMQ3WAGAEOXJZNEyxET1nQVXfxCItRlSWcCkL9U3QLuDIOUanG7gYRwrQhdNRXucfeaIFFEGAyXH2K1ujz+ZY0j+L3WSS6
*/