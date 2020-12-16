/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FUSION_ITERATOR_10012005_1551)
#define FUSION_FUSION_ITERATOR_10012005_1551

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion { namespace detail
{

template<class Category>
struct to_mpl_category {
    typedef typename mpl::eval_if<
        is_base_of<random_access_traversal_tag, Category>,
        mpl::random_access_iterator_tag,
        mpl::eval_if<
            is_base_of<bidirectional_traversal_tag, Category>,
            mpl::bidirectional_iterator_tag,
            mpl::forward_iterator_tag
        >
    >::type type;
};

}}}

namespace boost { namespace mpl
{
    template <typename Iterator>
    struct fusion_iterator
    {
        typedef typename fusion::result_of::value_of<Iterator>::type type;
        typedef typename fusion::traits::category_of<Iterator>::type fusion_category;
        typedef typename fusion::detail::to_mpl_category<fusion_category>::type category;
        typedef Iterator iterator;
    };

    template <typename Iterator>
    struct next<fusion_iterator<Iterator> >
    {
        typedef fusion_iterator<typename fusion::result_of::next<Iterator>::type> type;
    };

    template <typename Iterator>
    struct prior<fusion_iterator<Iterator> >
    {
        typedef fusion_iterator<typename fusion::result_of::prior<Iterator>::type> type;
    };

    template <typename Iterator, typename N>
    struct advance<fusion_iterator<Iterator>, N>
    {
        typedef fusion_iterator<typename fusion::result_of::advance<Iterator, N>::type> type;
    };

    template <typename First, typename Last>
    struct distance<fusion_iterator<First>, fusion_iterator<Last> >
        : fusion::result_of::distance<First, Last>
    {};

}}

#endif



/* fusion_iterator.hpp
j9SG7FOMpuo1pn35FyqcFqntdSp+6vuRiMqF1yieueGc8Wl9rLooB2acfXqRtYblZdtNKt658NzZtqL/KnMdtEY/A8P7f1ww2M+TBE3aF6Zy4XZRYfhKzy4HTqHhCNbw7V4Fp6SiISCI98pfKthKO89S9CYXqutZdnOPmu8EBVPCUD5ktwPLukEl40E9BNcXVM6aV75gDgfItvVzwmA+sxDqCAddNp89Sw7OwZMpCi4Uj6H56h2Wi2dvUfv1VB68QdmFqmvzcBodsnX/ZnhhHMhWeatvRB5Oq2zG5/XSo3m4Tchd23kiD06MpK6b5OxrVC4cu8pZzKRfjM7Dz+ODlYtDF96mynVGko8Tqst5FtU3TuJw7tF+yG6ekZkwW1QGrGq8AUNM5n2+CQYMVghgyvcYMLYFEwI2iqZnognn4MHoH4uHemZhx/Ao66x2h6395as9DJi7f5t2w6DWXb+K11xwyDHqTzcMQRi1ay6Ms8KmOsNPxxz43NJmWtOAgsoWLnfBwuHSUJBmrrZ3E84zGea98StyYNyPg9X7XZsD5/R+pdmLuK4APGeO+PU5OBhPyOgdZdYVgOfMkVmfi4MdGnP4bsuH59Ihbs/FaW5rMubw31EAbs+h/RjvT8zBwW83rQxUrmhrt7tljk+I3t0xnpyyTsWI+/JwV4Cgzo2ifyoAtycx5rAeKoAT0XurergQ3J7EiLVbTBxbh0qBax1NDZI2M3/hAnmYSx9Xwz1DcuG26Wh4qCQXjnkIDU/nwTED45n4zIgCcPwncRPeax+a/JfEW1Q226/p0Dr/eS4cOkx7+iIXzjr6OSTeg9crC1962BQe8eEoHcESK5sDKK6hT9EDNZ7xOM/S0Ard800fVAhHz6bq1delbKprWu3wsioYZs+6X5nx7ZOF4xpcvYORvdR1eVOdyrm3yX3yFHJpTYtQc8m1SO5bzOvWduc6l43ebZX7eghLUGskX+mpYBwRCnX9DX19mbHPpDFXU6B9Ntc+0xP0fc0h/YySb7e63p4o0et33We9nZ03e6yh+RNzXWfHEaPWf8cFQ4l0v60q7cDowPOcgrLDd53r9pNnPPbIWdKq6pC6L/6xgmM6otG5Lt7K0o86uWVxiMTHrZqxNomOOtfJ+2pDRg7He+o0zJa5kRP6/+nMR18OXXWuJ47MXkfnzOsQIK/buzd02zOqp3M9aPuTlkhDsDlAUmzU8dY58t6G2jqB/Tj3xqWstLrXtVaTgvPMrH5mYFL23hyT0H0oJ37nm4w+pzxL4fCViRb6lBJp8mGlwnxOpSO80tKpJl66Q7xp0028TEd4U2a45hNnd4A3rdR1/pFwZKBT2JCStQHL5sitOlaNMWDh+trSqd7DHA542ZqDF+0Y79DpMwx+5uBNmVY63Zlv2pTpel9jO8Qr9U6doenrGG+K99BSTV/HeFCq1012jDd98lS9XzGuQ7wZqIbiu/czjSftaLqyi7SUHc4Le1X3RJ178NE4E9cz6t5/KRgRp6E6QtwQhg+IGvAgblz5APN6i67jxCH6OuS7+pvWYz3dMCxDGL2pUO69lL/4K1ynmKH4zhyFcZjMPBv/XM9ls8nsaSQN2JmBcNAFe0HClofZFlE8rGGeLySsPQjAYe5TcYv3EWZhrcsa6yOajh9c1yeba1V9lZ0v+7UbJNOqYane2fuy6S+MN3ISfx83jASukcrIqb9R4h4aju80nxv0hNyw0nY/afR1Z7rhjIB1bmAdXwCuA4s+W64ohGdLQvdBo6fk4Ngxw8h5PLVuOE8j8mVD4znaXxhwuwSmoek6ozX45MhF5XV982CTXbWlJx8u+ayfQc/HkShGz7K/gUPqLszvH453w8w=
*/