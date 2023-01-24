/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_SIZE_08112006_1141)
#define BOOST_FUSION_SEGMENTED_SIZE_08112006_1141

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/mpl/begin.hpp>
#include <boost/fusion/mpl/end.hpp>
#include <boost/fusion/support/is_segmented.hpp>

namespace boost { namespace fusion { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    // calculates the size of any segmented data structure.
    template<typename Sequence>
    struct segmented_size;

    ///////////////////////////////////////////////////////////////////////////
    template<typename Sequence, bool IsSegmented = traits::is_segmented<Sequence>::value>
    struct segmented_size_impl
      : mpl::fold<
            typename remove_reference<
                typename add_const<
                    typename result_of::segments<Sequence>::type
                >::type
            >::type
          , mpl::size_t<0>
          , mpl::plus<mpl::_1, segmented_size<remove_reference<mpl::_2> > >
        >::type
    {};

    template<typename Sequence>
    struct segmented_size_impl<Sequence, false>
      : result_of::size<Sequence>::type
    {};

    template<typename Sequence>
    struct segmented_size
      : segmented_size_impl<Sequence>
    {};

}}}

#endif

/* segmented_size.hpp
V9JWllCAUV1txu1wjClcoGTUxqjGNN/94U/RBe3bf4quFD7srhgriKLLFEPqu/k1lRkG11H9m0cc8krKoM1GI4x/VN9PQZ2aGlFmG9egX/8/9r48sKajjfsiIdQSSwhFL0JTW2O/9iDRi4QgCEKD0NAgJdoU1VgbIqg3dtVUUVRVW9VQNJYSa0NRVNu01eRclNSaaiTfOfP85iz3nuucvH2/76/vWn7zzJwz88z2zDPPLCfAUX5wroq2OQoGqelAxy0NbXdc09BhjtMaOsKxX0NHOXZo6BjHeg2d4Mi6dtu1p5rTB9/6x7Dts3J6cE3VrgNpiIoQ7lwtlK6eFWvlr5GSWVS66bXUUHYpc4Sw9kFhEQu7KIZJZvXgCFyhJepo0lKk9GXdnAYW9m2hbun16rIzBLdmlbIIHesVqnuIXa0lRRjk6OPHbnNkR46kC8QcfUjllGzbjq7klq5Yc7Qit7TJy9EqXJHlz5K/dJTKUWmkMgMvRW7JqO94NELxP/KjIhX6RCq9sWukWqxGUNYS2Jiwy3hMOPO329xFIHfMvDFxhKJEtydO2Og0aISijlxJUUwjnUfojFRxpgbJDu5Z4iLpspREzgClYM9GKoV/lvzZQLqH/KWPRzu2Ryqz0OoTBLmQN9Dz2ZJ7AT3DKnTBAKUSpw9Q4pmken70gFznZpwiMSdsHiYrW8ulAmSCOvtUkWszfE8qR1PDVb18
*/