/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05042005_1037)
#define FUSION_DEREF_IMPL_05042005_1037

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type element;

                typedef typename
                    mpl::if_<
                        is_const<vector>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.vec.at_impl(index());
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
xvoJlDnG+p0oc4z1D8Q0vv/f9pjG9/+rchJnVzu5/1+NGrfPL5+XV2gqk/KNTfQJ1DbRJ7DFSZ+AwX7fjWLuiopw+/XlLPUc7olHlUZx/rzcsrkG83YzHcZmxNvt2yDbZdn1QfCwyfv1GRvsX/oM1DKjARz6B4xq20Jtx/3Hj+sIKlPKvaZ4PXF7UGG863VnP+c/ustDlj6DWhf5TMtnvAojyetdbOtZ+WI3jEEvTMbuOBZ74UTsjVPRB3NRj4XoiyXoh4vRH6/FALweA3Ed9sW7MBifxX64B/vj5xiGC2jTAPwODbKufzh6YQRGYySOwCicjNFYjANxGQ7CKzEGk1wtMf80jMVijMPzMR67tOFvgP1xKEZhIsZjEo7CYZiOyZiFKViAw7EIR+AqHIlbMRW34Wjcj2PQtS3f0OiOYzEAx+E6TEcf/i7jcQFmtLCPIUrrY9CSlrSkJS1pSUta+svSXxH/D4w6cdf/P7Gu2W93D+9WyvU1/Lo1e1Pu/x9mF/9zdLUHQOYAVKIkp+sAzrSsA/i33K/e1MYWl3aQOPFwZ1lfvUHsZzI/j7fFsg7XrCvUuQOpDvFomrpNWW5FgWPsaVTnBSQ6iVGDnMSoUf+iOHNqmbk9DxqurzBN21mZtHb3Oae1ibbEmXoXee/Ie6oKfckeSoGizBfohgnoiaPQG8djb5yHPmjeHy6U+8ItRz+8FvvgLeiPerln/A0YiFuxLz6FQfgOBuMn2A+PYgiWt7Jcc74I+2MrPshh2B4NmInhmIsROAsjcQFG4XkYjatwIN6DgzCUz1AM3o6x+CHG4dcY38K4LlOL67SkJS1pSUta0pKWtKSlf1T6i+J/Y8EJiv8PdNep99gqkvhfiVEM+BJ2IsjaH6jG/xw4smEnwF/cB9C5QR/AXPXabI2tLMJattFWFmktq3XST7DlOPsJjtUvEO/QL5DYRL9AiUO/QOp/sF/g8jKl/IkZWbOXD6zK/+zOe0p1Ge1+M/cLUC7vKXmvVaEP2dXu+rMBPTEBvXAU9sLx6IPzUI/foC8ulP6A5dgHr0V/vAUDUC/9ATdgX9yKQfgUhuAnGIpHsT+6t7Jcd+6CBqzCcGwv8b8nRuEMjMa5OBBLcBCehTG4Bgejh8T/V2I87sAh+BImtLAfwKT1A2hJS1rSkpa0pCUtaUlL/4h00uP/WebHOXknKP5/3+7+fwflvujufpbrtC54Ojn95w5KrGY9crFR7hNfrZPUxNp/NVhuF9M7xORldmPNJa4dXrYwt8RgLd/SsFzibPtx46UO90wvd4iTh6vb6B2u84eqz4t4bh+rn2kbF9DG2f3Sh0v7WnXaLGsm3o87LOfIYey7aV6JxOnW+inW+r/a6qc2U99kra87Xa2f1kz99db6p9jqpzdTf6+1vqutfmYz9V1bSf02tvpZzdSPstZ3s9XPbqa+0Vr/VFv9mc3UX22t385W39hM/Set9TvY6s9ppv4Ra/2OtvpFzdT3d5X6nW31S5qpn2mt72Grb2qm/gXW+t1s9Subqb/ZWt/LVn9JM/UPUH877uhhq7+scf0/1ffkvI+pqT6plvc91ZUp5flL27g9XODT9fXtIweuvP+SGZa+p0QX+T6T77kqDCBHKQWy/oEv+mIw+mE4+mMCBuAoDMRMDMIyDFY0jylBzmGIIt8foYpu9CkpnsqYEsV29C0pdqBvSbEjfUuKnfkuVvRgbIliN9ql6EUfk2IP+pgUveljUmSATAwu1Vv6mC7GWFyJcbgG43EtDsFNmIB1mIjfYhKG8mKHYT4m43WYgi/hCDyEI1H5/0Gq9M3tvdb9uPur6rX+Ki1pSUta0pKWtPQfTq7kWSc//lei/z8=
*/