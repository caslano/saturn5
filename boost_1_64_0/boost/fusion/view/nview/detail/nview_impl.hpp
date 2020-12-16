/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_NVIEW_IMPL_17122014_1948
#define BOOST_FUSION_NVIEW_IMPL_17122014_1948

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/view/nview/detail/cpp03/nview_impl.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, int ...I>
        struct as_nview
        {
            typedef vector<mpl::int_<I>...> index_type;
            typedef nview<Sequence, index_type> type;
        };
    }

    template <int ...I, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline nview<Sequence, vector<mpl::int_<I>...> >
    as_nview(Sequence& s)
    {
        typedef vector<mpl::int_<I>...> index_type;
        return nview<Sequence, index_type>(s);
    }
}}

#endif
#endif


/* nview_impl.hpp
JPIr1cZwg3gOI18nCAm7mxQqgDW0dkzGZ3r65xTPzoCvSRbTVd1rbyZTXgczhiLWl5hTIPLnjLV02CuLqM/pAbA5n+SQoVYOjSG553+Eg+8/byuAI0kfjsPnwglnUy2crqKP2Sy1e42wgvMNgUOcB99p24gpzEbsD8s6kh+hdu8ZnuWXmWnNkHCf6qEC+IJkcbxxJlxcdLIJTYc0shEZau1lpD4sPW4pcIj47ZoCeIh8y6kohyu0gZOsAJ2niNbPfKVzozEiMb00CgWve/BrgbjrfgK7674fODXyqTSVvqXUq+4CA9uDowwmkQxORBnc9erzlBHQGTZRd+i1hTLz7r3+Gp/fG3Z6McMp2NY7DP7y2HphRxeCRrxPM+6gXN5gVciDdI3+oS6zFr1NXtDlkVAorMX7+dk38v8n2QGnURMw93zKC+kEa2mNXBgnk/+GsFnQra35Fu/luj66UPQ/Pwn5HTt2Cdm9DrBMo3NdXUFvHk99fYNLVu8Fevk+9yKp19e1UiPw+Mn9Kvv3K8KXwvAhzvJQoCbkanAcjWW1wo6eWIXvYOfxPr8nMDPsGOvDQrUlxU6M6+CjqLioZED/wf2Lip2NDU4k2Tkz3PwmBMM+0eXXL2yFriNHTDmyfHTbUObyNKFx+De0BfX5rdA2fNIJ5RVtQ1rzd2pSti90hVql67jJIye1DVmNYW+IqIqO1YwtNHMwoXx6FatD2aQ/rFldDuz6i6UErR7irPL5XSEfWqrR/og31OD1+FwRr7PJHQngUSNO5yZ3KFLkd0V8Td5gKHBK5aDi0gEDSov7FztRzT1OV4MHqap019aFI3WV1rzyeJucNDemDHdWNL9q/GT8tWRAEXLVbyBCDBYNlpoBkypGxPI0bFwhDCGb4TZqRH3+5mG0e9B3EI+sf01b81SDU93vqfeG2oat5rjB+EIooe/Jw76nRn3r33xPWlvzhI+w110TbhuW9jInZuvr6bfd+JMi6XtCZtyBQJ3P2zYsmX76hEKRZ1GtA3w5fmVn6jmr72hn34XrKI+nkDcYCEXaiKfWv6ez9WXRf5XEU3V9BI2Xp004avYhJxfCofQd1eoAQ5PIPMACvawz7aVSANIl8WMUQPZFZrcZP/OchaIPh09H2nf68kyKz9EdybT6oe7tL4kfXJwqyYNpM552uAphHtV8PAV5OvfiX4n2sJ5D9m+qJm8eYcJMI5ZjDQfbyN41xzurC6EdfU91yMPNvRe/YELP1FM14gl/NEk8uUI1TZUNAU9b2rvpyFMP4qneqNG7oeZEysjW0xXw1Ij/CEviRbzuiC/QNupn5j0gX52IL2OH2XP1sjEm9DzdQ3Z8ebx0G4GshesigWCbMNa8nzqlEDKJLz/yNfylgoHUH18v12h9kjiv8D6Uu85dXdMmDFm+EfK0H+2JA8jTWwsmvE397vVVUfUP20viCdfccGOw7Rbd5hhwfSF0pe8piDx5Nt9OtwXnC38vqMuz6RG/u97r8je2jeZR7AJ5Gkk8zUDanSPW08J7lm71o1+I4xmSeMLKma7G+kglBlVc9ZXhiMcXwI4Mht0ItwmXzbqIPFqx+xCL3Z+hlxGPoyTqome23wgeY8aKr420kc6yka/xxFcY+er6SvsbqE+2nmrVm9UAukjiq5mhMFr5NlqPW/drz9WtDdQ2TZ6NN1jyuep9p3pDbaOAVu5ig+1nNOoAJ4x59TQTOldfSXzNkqiDNY2ukKdtTaK5r38G7TztgZvYHnimvuZv9sANbcxXpcmY4RW6Iu7aNtLEveniBa3G1MaOnDRh5Li2iRDVeUN+b/2/ialdpC9uhTZk9LgJFaPHjywZUDzCIPBfCwu/lkZ/xIc=
*/