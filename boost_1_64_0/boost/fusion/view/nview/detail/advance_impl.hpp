/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM)
#define BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<nview_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type iterator_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::advance<iterator_type, Dist>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
rK0PFBUXdzuBiH2MAucbZOWYmnj71fOqLYct06Mh2QQRhYFpDO9BwKf+FVnduYmS9BECbCN0zBEjoP/5H+r3niuPgqqQNXJtIqwFKXwyICtqEDO/0YHiHDEddOCAen4+8I9HNIfV0vak2+Xy8R+uChHtiwgB3g8uyRFXwX5gJR3tWNu7To9WySaoFdu/gKFGZoREypMWhAD7zmNyTP7ZXyj/rFJe3R68h0MY/MYIiYSnLI750dnz6znibMg9+dvievVY0P7hJvdqOsdd7gh9lPlnCAFeC5fkGF/BAvTP/bBGj14jh7pgX+ToeQokqn2L6LoOQoDzcVfmiFtBBlIBFmxLuFqPBuVAu+cQox7UU24HMD2Kq6/KMT5znHT6zBW8OXgRAuk8ZjN9bI2j1TniFOA/XgFu6jR9hx4dJvvmQw6Sm+FsJUIg3emSmT427+D7HFEEe2GCej75VXvIxS6XV2fCvc1UhvpuQCD1XggI8DugEiwqQAcSFWDolHWn69GAPP1oyMFpw7YGkEVMzPSx9tARuaI/8J+kAHunjNmnR/3yRfALsjnOmSMEUrsFZn7DvxiQK86FdyBZPY9uXAo9NHyynZ2HmsD2/dO6BP9S52zzxbnCD99/igL4905YpUfL5D47ZpjBcKYWIZDyRA0hwGtARa6oAx1IVc+HG3+ZqkdL5UbgelICT4zAIrE2WE2qBYAA7wVVueImsInTFKDtxp7XQ9Tc9KKdFcdQJz1CImVGNkKA76iNyBWXQXwgXSqZ3HAE1EgvMb21pnPk5AOJhGfszTAYm3hUrpgGd9gzFGDewheB86vkAjhj78txhhChkDbRAKPAupB9b644GdbFTAW4cfY55+vRK+Vi4Hwum29Ae8CMUMTKYXKuGA1yyFKA1W1WbdSjQ019k+1xnHIgO2R2YsAx5Cm54hCo+eRSgN43tZ2tubxCTk4CG4HjrkaEwuF06RaO+VHccHau6cGarQDBCRcN1xxeLtckQ8wsmUsHQqpaOen+aBAgX3FBrunln6MARS/3Bs4vk88B17vY7MRQSXUwTCsDheDge28OkWtYz5CiJIaKiogy9mOQHLQsLm1BWRT3ZJBFcc+DlsXglpNFcRFlUDmK5KBlcUnLyWJkXZDShIrFYs4ZFuaKw8GezleA2ze0hhrqg+Qy8K0HpvKtmbTOtZk/6lcuyxVzYM8oUIC/u/hgz7hY1h0KOYqH8vFPfN5mECD7Mc0tjgXf2quer1QvXaJHL5JrM8B+TOOKLzQQpm4jBNi3buUWHUAPWinA0jO77NejF5reOl6OXiqB6mHB6oD1KCHrrfMvOIx/3dotOoMcWkvF7zVXdoZVQM6CN6MpmaGXv4NGXzWVN9Ech4m5He4WEuTQRv2Qdn8VeFIXmLpQizh6azho1BB/gKiR839iMu+Ikomdm2C9E8f071WpuT7f9PFtTOF9R3x1tfQvCSBB55JFbnEhyOIQCzDn2yI9ep5cY9/54bgb7SDTfy2Vz4lw4P3zDLc5nzwUnU8OkEM5e9BEaSQ8pGyOw/ieZ7rFEJDDYQpwhDe5T2RQnVx0BM63J/Kum+WlVLYUwoFr7Q5wi4kgh3YK8OBT86Gu4jkyOx7kkMD7XgSrg/SCACQof2Og2/Tra68AA4vHj9GjZ8uOufqnBpZzG0Mm4eFlcxzGvhzqFttADocrQEL153vsytMVsG+MZ7EvHTTSxWYwklg7c7hbnAey6KAA00ftnqBHz5KVWWBnpvGuE6Tp7/+Bx8ijwS1cIA/Lrrpx9RmjNcdnys1JoCVJvLoRosvywEhiz/nHRG3OI5DNeYbxQYSCuBllUetXJUOJelv+Cxpcg0/JIxnkcaQCLFw=
*/