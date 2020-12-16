/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_DETAIL_MEMBER_VARIABLE_HPP
#define BOOST_PHOENIX_CORE_DETAIL_MEMBER_VARIABLE_HPP

#include <boost/proto/detail/decltype.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4180) // qualifier applied to function type has no meaning; ignored
#endif

namespace boost { namespace phoenix { namespace detail {

        template <typename RT, typename MP>
        struct member_variable
        {
            template <typename Sig>
            struct result;

            template <typename This, typename Class>
            struct result<This(Class)>
                : result<This(Class const &)>
            {};

            template <typename This, typename Class>
            struct result<This(Class &)>
            {
                typedef typename boost::mpl::if_c<
                    boost::is_const<
                        typename boost::remove_pointer<
                            typename boost::remove_reference<Class>::type
                        >::type
                    >::value
                  , const RT&
                  , RT&
                >::type
                type;
            };

            member_variable(MP mp_)
                : mp(mp_) {}

            template <typename Class>
            RT& operator()(Class& obj) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<MP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*mp);
            }

            template <typename Class>
            RT& operator()(Class* obj) const
            {
                return obj->*mp;
            }

            template <typename Class>
            RT const& operator()(Class const& obj) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<MP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*mp);
            }

            template <typename Class>
            RT const& operator()(Class const* obj) const
            {
                return obj->*mp;
            }

            MP mp;
        };
}}}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* member_variable.hpp
vN6Cwqu81GhKxgTMCLWhvxfNx/GXVpQWK9wkmARTxjhwJo4O4/ZE4kwc2iETw/PR1t0fNJWJxTdhbIQNFmYKA6UBGdtlfJHE0KSG+7eY5aaFXN6TDI4e/pDbtSxX0tgl5upccIkKQxrHq1vs8BocG5wep3bgPJMcYwcxvcZot41iX4s8E/cJx+KhPMfN/aXlBkNmpIhVeiXTRpqdSUpsYpidF/e2pmbcShLyXjD2nR3915/RBe4Kw48Ckz+HL5QJ3Omziw0Om2TIWlY6l//IRZMvaJOINUkiipi5XebuWrBt4TsnTJMygJeJa0Q4c8BC18iaKgrf/mk8z8D9pPs2g6VsaV2NH/FNmDb/MrDUT4JIn8h7cL9+8sHgTiWpP5kdRKAnOhTvlMe30xcMP2jEc0k3SJ1QoTOYsmT+R2J0hLaFnmNihPUpvtT1sCZUp5E9Zi5w+yYVOFhvdKaVkdtBweX7M3MxaWjNwYm4XqcuxqVBi6n3ADguKfakYrEIyxqAezT2D3FYOF/gDHxmyDSLSZP8Y1wa3DHUaJpVdZrzf4qVibY7KR2wW3SaP85XjnBCE+vzF346qIHGuPb5VAt9b5zjuLt400sNT+9HBsMVE+ZqyrvnTKCLl00g7mnPRuTBknBct/PnNI6ovNwz+pL8V5gXnYChJmfagDRNvhuWuOWXZxmmDrqvZhwaIBIsx43jd1sSloFakMCTBvufkLzE0fTcyR4Tdy6ibqN7+6CJm7w0Xhae91nHj18Rj8cQAaM2aEvVfqYv/Tumzom5kQppTF+NryMMrxOK/3N0GY48Mq6dZAkSHY0/9YQYvF2CjinzSqd94xPx/bf7hvOAMNQOiWebsfaJLs4KvP5skhkLhHAdSkuGtsfNHvIha8+ikUx7da+WzaYXtGcRDCrbezC/qJhkP7qf4ljrL6jXBn3fPlwtb/QlHkW0xRYNbpl4AnxHTn+g+FKEXRKJhf2YyvrAVcBtW5EIopVUKCNle9P3RcH3fKle6i/msuppZ8/fgyL6YoeucwCEeEOGAFNr9OWaKfF9qfieTgRl/zFkhiwIsoawCIj2qCV6ENEWSRpnRnTII+hGKspzPfKkV0oHmulcHvkmrqbvi/T3Bt5rp2/X6G/9T2kWc9VqA9UGNxBDX2no2PWs1gcCEOZKot83kXUZUIgU8NkRBHggXpDPQMFuZ5/mdS3R7yfo5Gtt0q4WNKxb4CGUKUr6/Z20VAyiIw837yy8gBOc9wO4nKG81zAtMu8HOmmbO/vyT2U6/jK9DtcmpaoDotwPlunxIG4hx2m7mCaaGrpJ9IdwuZx3aTUPYN26UTHDdvSb/B/K9FD+a5nG+UtfLPzu4fqYCvrfF4E+j+/o0SWgx/iOrl8KWox/aOduoM3jH3ri7qDH+IeevwK0efxDO/cAfYH+oafvBewC/UPX39vBTuAn6LNXRdA38TnTuRVEn8d/9OTVhGH/UcN/YCXTfL9CaixKi84Meox/6RzR4vxLu+4H+gL8S0dWOziqBE0fu38UfZPJZ+pa0Bfgfzr3AODm8T89vIborv8p0U89UNH9aXFwIvCTgApyW5x9UBS9uVX6YS7risSM4t/AMa/hh4RxFMXX8Fp3XSwGzFjuZQ8N48bbe01ex8N0TPdj2G9luU+vjcGQ3Oad2Ycp3EJMQ/QXneYRlCZ+2Wj4H3+kwi5ouWTSHH20SrOg5VJiC6W5bb1Ks+CljynLHY+hdLFLP8a+87GEjV1SchnGNirsgpZvJs26TSrNgpbGJs2lXpVmQUtjHsMehzRh/2bW062Krl7fibLGGXe7wUVZ+pzf8euBc3yH0VXZJ+rxITrtR3Jel8IYdq2WY9MTgJs=
*/