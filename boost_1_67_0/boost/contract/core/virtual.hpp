
#ifndef BOOST_CONTRACT_VIRTUAL_HPP_
#define BOOST_CONTRACT_VIRTUAL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Handle virtual public functions with contracts (for subcontracting).
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#ifndef BOOST_CONTRACT_NO_CONDITIONS
    #include <boost/contract/detail/decl.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/any.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_OLDS
    #include <boost/shared_ptr.hpp>
    #include <queue>
#endif

namespace boost { namespace contract {
        
#ifndef BOOST_CONTRACT_NO_CONDITIONS
    namespace detail {
        BOOST_CONTRACT_DETAIL_DECL_DETAIL_COND_SUBCONTRACTING_Z(1,
                /* is_friend = */ 0, OO, RR, FF, CC, AArgs);
    }
#endif

/**
Type of extra function parameter to handle contracts for virtual public
functions (for subcontracting).

Virtual public functions (and therefore also public function overrides)
declaring contracts using this library must specify an extra function parameter
at the very end of their parameter list.
This parameter must be a pointer to this class and it must have default value
@c 0 or @c nullptr (this extra parameter is often named @c v in this
documentation, but any name can be used):

@code
class u {
public:
    virtual void f(int x, boost::contract::virtual_* v = 0) { // Declare `v`.
        ... // Contract declaration (which will use `v`) and function body.
    }

    ...
};
@endcode

In practice this extra parameter does not alter the calling interface of the
enclosing function declaring the contract because it is always the very last
parameter and it has a default value (so it can always be omitted when users
call the function).
This extra parameter must be passed to
@RefFunc{boost::contract::public_function}, @RefMacro{BOOST_CONTRACT_OLDOF}, and
all other operations of this library that accept a pointer to
@RefClass{boost::contract::virtual_}.
A part from that, this class is not intended to be directly used by programmers
(and that is why this class does not have any public member and it is not
copyable).

@see    @RefSect{tutorial.virtual_public_functions, Virtual Public Functions},
        @RefSect{tutorial.public_function_overrides__subcontracting_,
        Public Function Overrides}
*/
class virtual_ { // Non-copyable (see below) to avoid copy queue, stack, etc.
/** @cond */
private: // No public API (so users cannot use it directly by mistake).

    // No boost::noncopyable to avoid its overhead when contracts disabled.
    virtual_(virtual_&);
    virtual_& operator=(virtual_&);

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        enum action_enum {
            // virtual_ always held/passed as ptr so nullptr used for user call.
            no_action,
            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                check_entry_inv,
            #endif
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                check_pre,
            #endif
            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                check_exit_inv,
            #endif
            #ifndef BOOST_CONTRACT_NO_OLDS
                // For outside .old(...).
                push_old_init_copy,
                // pop_old_init_copy as static function below.
                // For inside .old(...).
                call_old_ftor,
                push_old_ftor_copy,
                pop_old_ftor_copy,
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                check_post,
            #endif
            #ifndef BOOST_CONTRACT_NO_EXCEPTS
                check_except,
            #endif
        };
    #endif

    #ifndef BOOST_CONTRACT_NO_OLDS
        // Not just an enum value because the logical combination of two values.
        inline static bool pop_old_init_copy(action_enum a) {
            return
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    a == check_post
                #endif
                #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
                        !defined(BOOST_CONTRACT_NO_EXCEPTS)
                    ||
                #endif
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    a == check_except
                #endif
            ;
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        explicit virtual_(action_enum a) :
              action_(a)
            , failed_(false)
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                , result_type_name_()
                , result_optional_()
            #endif
        {}
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        action_enum action_;
        bool failed_;
    #endif
    #ifndef BOOST_CONTRACT_NO_OLDS
        std::queue<boost::shared_ptr<void> > old_init_copies_;
        std::queue<boost::shared_ptr<void> > old_ftor_copies_;
    #endif
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        boost::any result_ptr_; // Result for virtual and overriding functions.
        char const* result_type_name_;
        bool result_optional_;
    #endif

    // Friends (used to limit library's public API).
    #ifndef BOOST_CONTRACT_NO_OLDS
        friend bool copy_old(virtual_*);
        friend class old_pointer;
    #endif
    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        BOOST_CONTRACT_DETAIL_DECL_DETAIL_COND_SUBCONTRACTING_Z(1,
                /* is_friend = */ 1, OO, RR, FF, CC, AArgs);
    #endif
/** @endcond */
};

} } // namespace

#endif // #include guard


/* virtual.hpp
46f3GJlH5DpYSWa6KyI4P5mbf/N5Y0XuACFyTLwrftUiUSo3Oc+IO3Ead3swFEtIVbvjDHWKCstImV2ddV+qrOmCXgDqaVkLXFYh1mpFhh+Qcejq8t5mlUeuxsb/3eOEgWVScKT7r7g2nEfTw2rHcOk99CPP4TWT51PjyaExjb8ZOHdQr8YJA+2IUImpO8YrVei725uaZ//xGfau8uFe3LgqRFdW3PkEPsFMWI5MZ+IVzPOwlXBjpqLgbFr8s4V+a3Pr9lwJUmrGo18OuVniiBiUQa+Ps1KvZRdeLPCTRdIQ7zFUNlTDgFsjDaby7Err8RYFqERU6cO5D6U4UFobUKxn558DLaLqxXGyh/jWyn/JseV+alwMDL8ownpqDK0tFZhnlvvPZq8NfOgq+un7df1ohhyR43uh5SX9CKrY9FEVxxnIE6qq+CNUzhJ25cx2E+wJjZ3QBU8oQUTi7TftWY/rJY78Zno3pRUON3j58ZsjNUzGE5QlE1ceGHvDJTQUSe8IhBX3Yfhw4wehHGZ3h45KvpTml5l4cciX1nxGLQt7buTzgVeFnXnpxkVyxQPClxcaJ8nfTJWYnqBEJzOHyHsh2OIdBBT/wYp6Mhmwn4B+hsLuQsuIPGmASRx8/lyb3zlb7U9GFypphTi76ktweHgWRcFV5YStpTs0mznxCbzw6XiNBMCC8/8B/Fx1T3gnAIBDS3V9y5LbupLtH7W/4dzb24OOPg7HNqP7TqEiJdIiCW6QsKr0rTfCk5qcH6iRBp3vTKh2D+zKtUjxAeKRAPLR+0dc+w3j56ypj6dAszm1F2nHfWI42url3U3hI+1p4Yg+omUrEWFCiriWGfdZmpJkLsyHkLy988JkpAY2jL6g38QD2uEc47LiKc13v0jABH0YeOIAvJsu6bf88YEPQX0GSwCxWoaux5MxMLjM7+bWWqDrUOkYQmkCoFUU/R3Uv7DqKzis+mJenxdMwVAU7Rxdb2nxei1DvccCqifN+qsgvkfzqSh+gGY0Zty3PZAEEIhaOpG4nheMM4gjO6dvjmWyH39GjoU3PPYl/PDT1jex0SATCBia/rCjvzHwd2zwxOhWiF36N5RpuNMevz2jpmj2nYXbtO5XMTUpQwpTtgKFo59+OOE1UjVVBBjgZjcDLjzf/w8DoDVNc3O1OJAismhwDhVd0HxzkGi1LftMxnDZRwkGpSVYMRSxWLbhZRiOWy5xzUJ6xG+m3RYOt6tzq87Pii+qAUO/RnydY+/C3D6tvIHfsPB30bR3yn2OqUNON2rjbQ449pgA/6qpmSgj26Drl/hiOw09AqxTRzGcdLSlE+JeEWw2XTFDJ5sbQh9lKTENJ7UXc9RFSN58+qq7VWMQNdn8D2NGaKNxTRa5HSO5xUYFXBPQAIPaWL2o8QPWWEclqYicaEOkY4paKb0WbRVir2CHm/rU7hAivNGCW68Qbdr0TWnoFeliSi4AW38s0/UIytiExcLGzN+ZoGFdm7yF1SKxx0Q00cORfOGnNQQGY0oicBDA0HFbecRqBOyvVKZ0muOv7vUGNSqettm93cOBZIwIMDaFFMjIPZ0SWhjAjOW8+vFjwNWyJ8jo4zSomSPK86DyYmcsoTZ8yJIQhzhcv0T2eSoq9K+hjO/zsU5haM4nM4Lhap6hPppRpKIeviH5cciPRm/Teby8V20jBE5pXAVBD6irZIAaNSmPOzqW60FxUg9IjwRfTAAn74JAqdJROdNG0MbfdkeDytDe24P74Rk/8diFZmri/wi4UHbaa3CUBBK13WBUCAz6fP+byBr0aV9yX2e78m2Iu6kF89r7MAITar/aNpLthKaGl+d+hF3T8lh9hKhWT2rvE/hSr4eHjhFIqX6G9YnQBTunzCyPKej+ew3L8S3wF07oGW/YzGiNiu1fOSwhmJL7O1Xd1QGJNnf1yVebjaEoFaHebsO8Db4pXt5wDqKj+iOGB3mcbI0FbYexcmsEmgcl1cbwbVpBiLFXAASTh1TP17y4EcTDEhcc8FlCmyckSeGP+MUeax8fCLNc+bOW0JIlfpB0GoQ4HIxjCuMl8B5+aVG6UNQfHO0ZaDfVrJDzYL2HeL1H/ZMW8KqZw1Sb8KCREa6+7Tr0IoHzr0s8A7OMsP/3n8aN+cVjySBxRZUN5n/fjVlimMSj2iS8PtmzIJacC1+dsB1SQNEOFGDcdQeopmHeIwK5zSGPBhKoGGgiPcStooyOXtZKCHjeYsXNVnTtTYOqtEJt5060zjc0WTSZxjkd9FDWlPVAoWlwTLfMNFshhwuX8/sYNyuIm+se4R4/LxL3Zv8DKF2VQhHzDqxfIrROjHBr/InU6THqVgbCp417pGiPIjQi5J5TaBOJvWzD+L298p6julxp+caBDhH1Ssb/2nMa9JlG9f69zlsU1zFOzzvlx0+TdiDbuIAHu+5GgGbvWjqIKTfJekcTmtgWluU8zW5wrbiL6L2kLxE3+8XCXdHYNnxcYz9C9WTSgwUqc/gWlDBhlxEY2uDwbBFAbeENzF4HRR8PEJG3848Wyqv5qmNtcjowvE6zxSL2k3BfFTO2T7Gy2CBSzVsZpEXdveomxgV14/Gxbrv80fkAiB7TDhokKxUsB62kYvb0VSSyQJMYDmyZLyfZVMHtSyqlLwr7CEgsFK9H4MHuJn9GGGps2CauHIdR5Sbp/fHGI7yLXERvoHlk0fTeihq6omT3eHiMPRJnnhyJ3JyGtkV/8pm9dEmPPp0LZkH4wTQOAAHiw/+3iAVbhojw7PIwhvxOvUT3Z7nCK3AjePRnqEWWpBEgJlLlqbLc74KR2vbzMGpWJmIxMrVuIBqK1gOPPnzUB64ODvYKYtkqHdmjz6BaH5Yf7dE3iSMfPQa1pOAwAilaWfz93jp5PXo0MOTPxfI5qfL6OJ9xcvyin4ehbOJaF4xCCOisUOsKYlqq0jUjJFR9QDm7GZ7DHwo3tB7RtoiERC3/3mJ/lAPTl5gbUGDs5nddtiBivvP/+pLLEg66tuWxwR5hRHw03waXjcW9/BEDkSDetnDZ3/rz314Sv+MSgiK/0e/rVDjCZrFUAY/f++aJ7R47Z9JF8WB7/yBioNdJRvb64w86rZ6+rHx5mFHNZOGuob90FKqnHrr3Ndk9geAxdL+bwU49/ZQ0mQF1q1wZ0fRLlfhI2TTBGPVjLN1jjDA8kADgxbe2bdu2bdu2bdu2bdu2bdu77/r2Lpf0Sfq/k85MMmkBCmsNyl2jlehcgGPDrDWG7/XM13m0NLs9B/HxGAeqyzw0uemRB9hnystASusPXjFIyxf42nNfK/L0P+7krv8LWeu6GsaLy2d5/pYKym1y2wiAKl1pSER5ZE0huvS139csTaKKlmXOKE7fzQRTM7RjZT7oBwxBYdxbh0sec9PpA4uNsk6pm9ymqwOTdEZoGcFenIKsp+YIsKScow1wFT+DLkG7GGfJ4I0Pgg1SdHj82X8LtcGFqdCbGZIW+3auKbVOWSdhc7YyxZTrZzlP8nIYFVrr1rWiKJhcL+guyNna23WguuMpvYOgGYBLPAlXgSgjU05ao/ObOqPLowVOskXPSi0FL9zJ2e8M1gaZzTggU6iMZKqVMo/p7VzWrxUD++Rq0EbsFLY0wCZhyQk9/KagVeJZSSyG+gqB5flBCrBRgVd8Y6wCcS5P5+xmC6CzwHSM/ibozSrsW0Z3ygE4jYc2KU1Gw2DU+JCgs8vmeVR0N4HJf80sRSGZfpqW4HDACTPrhpm32+tyguBUNHYgAN6g1lfnLcL7RBubz7hGmOuN0/p8MJhyaJlTk0XRoliIAEcMEvalFw/BuyWoKCnsyqxTeYQxMPBs+bnynmWa67kkoSFza6xIg7L93GRTBbdp9kt2Mg/yPkbrO2oT9+CjE94OcJM9m2WmKXbDnpDpJ/HlZ0Kvot/OnEsD5nIeMJ9aFUzYQLT02yzAD1JaT88uVHx1QK6tENcP8RQRMoGNBA8iPPfA1iqYPVv3RvAQmDHzxQaZifCQkeKm/jSlH0tJZWHq006k3lXNvp2hxJtg2oK3zAUWqsvwDDCHOwi+9OarMEgb/2kwUF9rnSH8Nkx4MUUe7DDFCikkfSNtJ75SpTaEk0yH+E+54u2l8hNseFT/Srr5A0qRGf5bvpyTZlzGjIihp93roAP+s6AhnlgMqECFyauofDSaWGtV01cB2mzEB5CwDVXoYe6W750Wv6/YccHWb4i3iZq1jR9ILX5tt0qv2JkjYhybuSgGtYtOQ/oKfo5hPBkpJ5/lV/JV6z852FJxoTxuBVvtkaQznrqsqrj/XBpCsBlvdhgAjTzM31ptBvR5ERXA1lml7v0fcR8bOVcH9q6a8AZVpP3QTSy0c6LHsGWT6ATIDzg18P+Dk4I0dIfw7ywGCdql6JE4qi8jNzungmNxZkIPmJ2jHKn8N+CwCKA9juILfSTOsWWKNW6OWwWwbIa+8EJKPwCz9V9ki2ZKIl0Dlz73IW5nC9JZt7rrNs/JmpDCaL3P8chTZxOJnbn1uHmdOKNvyMqcqHUJGNKdGodwx4p9DwiCKRAinn38ArwA5YfDOatajUl1F3rtileP411Vb/H9GxnfG00M0kl9X0nK7x4YByNxHQL4fksz5e68v3ePPiQBSbHp9jjkscloxS4cWW2TKJvQNehOqDaXB9eCKA3voFYfrJ1A4RDTc2YncLH/BzHgmDOJfpcCuaZrQltGWCUbhME76+cl0jjTdHymPJvdE910E/HZT2a79W7qUrILLjVAkm5YeZpde10ZDyzwhTHE+GdTd9h7KL2mEoil3mcrNfJopkisAD7cwHlw1L2qQApMLZfgAQ2LaBrvfRmwdBAQfadIwj7OWYdeGtnhJxNwj0ZWBnRsjGF4QRrWSMn11aKhD/V1c3EM/fhiEOPiKdD5eFQae8HsiTEXUbSc+ayKoAKBR4lysZMzqrvWXkPXNslAOr9TBwGlTiOlPZAqHIqtdD2fy+zKWujWSIB0XgBczkLXXpTo+pSXNISh9WK86yh0+/b2KdCbkYPUkMa2ua/vOZQoxZ4NFiOupSA6+QRgCSFS97/kTRb72ycSHlEg+iyWTpTkwmqhqnxS1xGkt4zNPD9sr0vxWbziO56lVpV7b3z1Akya75T+LmlyrC8L5LQiz7yr/FE/OyrZbiM6geCacIproPU6kKbGsCi2ZoWHSPxfkkcfw4BotJ94oFuafzdY3q5Ou8j4FR5focO2GFwg0gndPzsIkrnXYLUeTVG6DgSCWASkjfWxfjM+mXwhzWKbvtlrbSJtRxgkSdeFHMp1wGaPagh6feTvnof48VkIiLaaVdz0bRV0Mnlthr8HaqOzx7h+gjsQe4ZDB+5xjCLqBjd5daqLKXpdwQul65A8kbNjLjAay/GC/PAfwgE2RPyOfpDN52VCEUu6AawB3+OMUD1HsF2um9DCU2b5Pq85YSSe+MlqzDHejEOkvP+yMVRJEsKdeL9ghy4xQQdWdQEosNjv6O2bFIMzZmtkd8hy1HYNBhkaolKVvQ3to/tT6Pp/Awt+9QyBSBgveHd+PbhA/z35HRTfUpXb7rB93f3+on2Hod3JG1/0/Qr8Jnz9OK6YLN5+c0+vdiAl1gk1+sbffltOzHJOmWwqNOJpmF3suqSkEdcQ6mBzd74RYefDy8hcmx8KnmsPrtVXSgWPwZOea30B3vaeClBntg2buBLama+ayJ0+HHWKltET59AayFg2NqcbNIlDsu8J1tyNR/swHtXE2hz1df6buViyf1INUL6XZhgHUXLTyzH6T+knTu/AM4BxcCwRVohyHi/ifRKRzSxx4VxNmwZ8yF9xBqfSIPtcJcZkPA38P9Nt3efIk8xnhNc068HcyyhpcX+OE0gnWQtA8wjWrZd1aZm9UPjnZMw+yYonI569MAU3f94lklweuLHviEDe62c2NPtODiw28NwK7X+NM3cxNrM9e9askcoD2XO6x4FxYHUqzubdFAh5IqEOXx/1BHHiTpFqyLH7th+xCDHLB2LuNwe8Sh/m9xo/JWFV0CHkrDq8iE6LfWHFL8dKFPjzs2peGEwhbse890wm0B/iPnDgwJcYsKZwwXYFjd3RdgT6eYZwfqDQpS6kAk3WReYcNl3LWh7hTizgTXvxgRWGnfwa/bfEWAR9Nx74d+IIFIbceofe4xtov+Zoy68yjZf2HAlDoc6j4Em1XuyI/kiJrOiSQ5vMBUPzt5xt8P6jhKsQBCh11OOybnmZs4XDYvMg8ZcZrHUPl6+KzsUNerbiM7n5x4ENMBZQ9MloOBpPDDvfBRTWT87/SCaEjj/j/EFZpwTGN9SvPXNpI+JBaByRA2IcxM2FiYA9Z05yXPtvOANrsFOVp6GI9UNWi2nNL1o/XaqFwBR4wUZNjbQpDCLzD17Au/SEa4RijPDkB9Rm87N9U/+9I1j8g8M3feYPIxUDOHWmyox3BAD22mQH0DnfnBZreqCNWWJ4mKcv2IH/4lhbwY3kF1skebgjs7tA/imkNXvatJ/8GgjuDPlAAB8w4QfT2rwavnlhuaYcOkhZ4Y5vNUC+MJXBE2nSMGlvYkI9uIqnJ62Gtlwf+g2LKB3DN+cNPZSF97TfInHkAeoX0EsgHjlm7KuMnDUs7wQX6scktp/hVI2lOj3t9BP/ZwhTsGdBKgrP28FDaPazBi7JHuh67xhCRidq3GihTfFflMC+nissa1X0azvbRsm8wNw50MPtJQpiDR6AQttbPquh+cyCZTtAgtA/Un/VplMpPdyfwbSOBfcY83gWyjHoMiVNGfMifxdmI7ldavs3e413pjk1X/Bb8FwEWpUZTzEBzxgSh9VyO72Q+AmVtFN5loKGbpQHLkHmmkXM05LXj7YIJsFla6OF7JstVDmUaHJomSfZ2uq7Xb/h5eJo0pqz/8bThverWUPAwV7g+OlhcoMxGWjNo9LHNua25pe35e9fiMx3U3BcQ5Dz1fli/j36O0Nx4QHcwVEJn++LAOry51CSUl+Y+Qp2nawIo7oRXTdBFf/YZ5i+E23oi6eKXNMmkPRuOzTB1WNL8D1kiksoLt3P9tJ/3fy70z8LFBeF0CXwqCVUJFNefKKz+ObQSSLuvCI3Szn3I9eUq5ag4pxSD1BcnfpKZiS6Uqm9uVrxjHy5hME9ebKWqMUapPfO5KDmcbVoiQ09tBhXD3kMyUbfmE7I6DIxRc2mNmOFl/ci81n3qWYsrBFbXA01LOFIQG3juzS4NcQRiz85G28sBEDUBJk8aSMG6YDp8bwkYmfHJIj4od3S79DuiNWvQ+x8t5FUqeUKufUcunBiaBEnIFEzlaxySlDosMffsgOcPpBPbaLQQJQw29gVQqDqGU8/4Pd5AmdVijakU10d16VgxLrq1iRJHpkmuSKeFJv4eBtJr+LFFl9OEu+kMFZGA53oyQe4PVe02cAFNujRGogNLQnienVU4yE8D61GnZRS6M54AS/Mrsvz6GPNehEPJsYDR7Ne1wVntzQfIfaYF6s3sNor05DUX/sSfmQfs2A/iu1dibIvk59w1UzTaQa8M7BsxTOK9Oz31VabSh2edyThQOavKD6yY5FTD+q7ytkuiosx5oTOJK4D+sYt96ho1G7vC10TomN64rqgr1SUu/2M1KYxPDVbdHW3/5L2RXZfDtrxq7orcDFfcgBaIZieCoYAxhsFhaD1FLYfj3Ru+Dnh17KguxfiVZ6rczC+YWiA/jjmDNO0SGgW3TqdJQtk/FXmQ09cZcqeWkWOpunaMV3eQTRApCV7tp47y0k6/KHBAY2XtNzvFD+WOMoNX5jszV0tn15eCpOhvqLw0igYwcVouNZaQDfQYRRqjyWCVH/vgvVoGLocFtU3wuKiWIBUwUnz0iDSL63+UHPbOJbwFyhiki7HYE3inMaumkPsHuOMFI/iPLjFu0AsWheLRjKaVGv7sROTzoIK+6l8v+/C8CmXwqqf/w+ObnrkeaRTFcNDHnMoG4rhDubH3OFrm8ERVzAqOQyAi8VuveW+Xs1DlpqkpejlmA816WbNy54Gxd33KzevfMpolGeacCOXD098BVU9/BcCcg4DB/5wwmtTZcLgOkiXZ55yanQ6sra6lmDZ1FNt6Lh2N5RoGUMA2rzSOg1eeD/NxP9m0erwN0ukQY2tDoT+/vfxaG3iuULNYQINo22gz5et/1NLxzOr6dyCfOOWQChD3WEjR3efb35Wjrv4+RfiF+Y37ofIUPy8kCaS+xQ/qa8o9B8Q/osrf42GkQFhYCiE0IiagG4HAHOur3g+2LI9QpIi8ebXdMICHfTyQJxbA1i/PhKQ7s833jPu+bf17BRsUjq8MwxUXLc9AMrZh4WZ18grEMN9e1OfI0RvW845I2M1AyQIAfvsTUZU3BbtFmHSDSCTbcpjbMjQHQx0XZIZNCZaa1IIydEwqm/UfDR79vuXdCvCGHyM8e4XCaONw2YRP5P2v7gdCvlHKj3dtG0jRA0y/pbp89Deta4AZ880DcTApjBJMmoO7OPJb/mLu3wZa3RBdU7+RvF+sy03HGWbT0z8LiFdbqsS7CzQzxXhh4O9KcM1NEoUm0T+iw+kSNefDxpF959Kvvk2IxtDqVarsGgPNCJOqW6NEIkiMQzNuQtlZxLJ8R0hRMqKJTcAPqVuIa+3HbcMeJaHteCGjE5+rTJYdTuTzk16+QLzN45sspy++HFdS/wtQ9CIrY2z+PZaar92RR3mH6yokJDGy+p1gN/OXuk05iYi0zCqYkYt+ATZyClTcMEPjMEjI+0aevg1h+/DMjpMjUGMTa3sbzRkAKEtlP0bbrKtb5FAw9p3EPjbuyo5jvTtITry1/0NX6cDCNypGVawfXW/0ql/9S26/KmEgQeHTujCvYrg5f/peQ46AMLRt5YpuRsT49ZqAzkES2DyZ79fsqUXPPwoLSPyn+Y0NbeHGN9xaFLlmJv5Yu1Vx0VJny84eJj9FRBgHDMFTfzz3b/YMAgwbDnh9sdKswNRtK7BeMyBS/NGp61nTrk4Dzf9rrk0mv6JXlxpgq7oaaJvuPYkvTVHTeYPVxbxxdSuCzmCOhdUoTuh+iWhjeatQ3Lbbri1Yqsr/gHAUPnCNG4/bB98NLVIMLpfT/5XjbXY00McFVJhhGhqDNlqoXQd5yXzZATL4/zsq6rk+eo+qodpxtA2HjB6hf/SXYGlbjnYyAz3DFA=
*/