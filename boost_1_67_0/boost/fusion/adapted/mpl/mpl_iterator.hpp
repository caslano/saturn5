/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MPL_ITERATOR_05052005_0731)
#define FUSION_MPL_ITERATOR_05052005_0731

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/mpl_iterator_category.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator_>
    struct mpl_iterator
        : iterator_facade<
            mpl_iterator<Iterator_>
          , typename detail::mpl_iterator_category<typename Iterator_::category>::type
        >
    {
        typedef typename remove_const<Iterator_>::type iterator_type;

        template <typename Iterator>
        struct value_of : mpl::deref<typename Iterator::iterator_type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename mpl::deref<
                typename Iterator::iterator_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef mpl_iterator<
                typename mpl::next<typename Iterator::iterator_type>::type> 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator>
        struct prior
        {
            typedef mpl_iterator<
                typename mpl::prior<typename Iterator::iterator_type>::type> 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef mpl_iterator<
                typename mpl::advance<typename Iterator::iterator_type, N>::type>
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& /*i*/)
            {
                return type();
            }
        };

        template <typename I1, typename I2>
        struct distance : 
            mpl::distance<
                typename I1::iterator_type
              , typename I2::iterator_type>
        {
            typedef typename 
                mpl::distance<
                    typename I1::iterator_type
                  , typename I2::iterator_type
                >::type
            type;
            
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Iterator>
    struct iterator_traits< ::boost::fusion::mpl_iterator<Iterator> >
    { };
}
#endif

#endif



/* mpl_iterator.hpp
8SBu0oC7DhcKlTubIaJIr+JeQoQUV0l0mCGuajRZ8S7nZ+vzu+YBa8cElU/mCO8lBhds37J6t3KKpZjpZUK521kBLYBgwCiNHr/+MiLrh6LhxeHv18brfobt9zqf+yqOXgsINOZL6SYKMmWXVVzY5Cl/Xlqv6mHB7wkey3l38cHR+FrmexlO8rDC4aCHqSwDYsKZnnNW4pPaI2lxMbCoZ4VpKPrzVhv5WWV5YvYxzna8tvIeZjl061fpo7KotdsuejaMLnEm0uLSd8qIn74GIJzsVRfQs2T9XUntTZThTTOue6cEnnlK2WUWbIg3hGlUKgufuLMkeWUuyIgHFKvygtsl9j269vrH6M7yfVJq/vUPQ1tMdFW+5wL9CIQwnmWSRzqIjlNjNDi56R8ABQ1Nkxv40CY9wpMef9muwEgdILAXwLkk0hvHLq9C2R21jb22GSZVBc7rXHQXTYQ/JIdjeN94ZD2fNh563xvnE3xTut+MHT8i9kcSVu+zbJ1WUUdO2YGDp0bO6HYwBBACldUdNN8ZOz8vDTnfA9cpPi3f+ydvEzWkz7pwNZkjxS2fRA7P3ZHLOAnoW9RlqCO7Qgit4Ddedb83KSfa++5ki8674/Ozo38o4/Jaxd6NL17vHu6oyssiiouckTNV8U/0NGgfw++Ybr49Pw9sXrpfvZ/eNtoaMsKyChbn3fW8p9ky60TAGq1zBvUNJY7YwaBhxNR6UnZwf67ZxPi8ex6GzCZmcv5MT9d3bJwVGRLznWFJahEZNG2QsKKjIzEEywITIpAwHd3ddHO93V1dn8ipZWdNZV0dOycvDJWdHpay8ehHPZq3VxkGhFNYjMxR8LM3/l7T54UCPJtmXj4972Y2h2bGbp4Eymixe4kd+VEkuzId0TqB6cT7W0dCCLg2vZddnvvXx4+EqxlntezqycypaJsYMjQlrwQFuXWzqNXFLcw63f7E2lpHagTA/y/lxA42jldPw9ua4p2FwbsjYUMSJvWwYELXdeICEmupTpZhly9FnuGpOT72LaAG17u1wcGV8h0pk1c85k40HO1zoP1WduMYtmpZ+xAhTwQFqYEFPX5nWWDmj/v7bsflcIkQNBvwW8LsaTJf3SnMUfsmRRMHtYrTQ5A7pZL/0CwB/2tI6Jf76W7H63DG6X7C9pjRymgyTbc+xLFydeIi9n5ZpmNcND/aQB0zPoKqmqCsN9yN90bH+zDPz2Ac3xnm2iLcpAsY6WA1Sg/VpLJjQiAnswyMyEK61i7LUejX5erbcvu9KN+PcBbXNfY2Ajw1BBCylVm8NRTiH9lIfvCiMED09QJV1zUfjneNhq8qwzMZsT3RRJ69EtY0r4jHbeyxtH6MfoggZMrZpvnBJ3NNWABdFUE4H1Mbrwny7rwpboIYvIMQ1ro6UOEZ4QweSNZAAHuzAH41OWQ+/oVygNp6uuYfqsNhtn8RNvpKMQJGI72LYPScO/sZpQ7EF09567InXtnV4YTlwvPXjb2U23q4la7vCz/sP+87L3pfbk/vLQ5iOzKVPbIzOo9mLu5gaP/87LKISJfaNQx5fvv3gVt43G3KHznvd7oSvZ+F6Qq+Sp0vdp9XDeev5fho0xXPAKbn3dplxGRzHOk4TLEjwL3Uj6aWqfvjEh/ej/OYjhrvOvuno8++h831s9lN551Xfz4GA3jixmjcuuVxVAoIZVaEYEoNCznvz4EztJ5Nr7uj/wGSgG1/6sXL2f3LidW9VGEllpnyx0esgZjO7pFqDCxRB5bKAMKQ5Yj9+NPJF1/tPH+1fHFV2NufWF1LFWajmXFffNDaG1Tb7RK1him8/VZ7UBuslJebH786/eLV3vPr1Yuj2f2N3OpCupCLZYb88ai916u1m6VqJUsowFLJoLZyxB7/+OLki6vd54crl1tz+8Xsaj49MxLJDPjjAWvAqbUbxBoZS8jGUgigNlApYo9/uDj7/GDn+cbKxeLs3vT4ymi6MBjNhH1xj63XrLGrJWohS8jAUrGgNmD1+8ujl9/vHn22vvVsfuk8P707Mr6SSMxEwqM+74DN3KtT22QiNY/RTsFSkMC25pJmcvld8fjtzNaziaWz9PTuQGY5lJz2hEetngG9pUeutApFaiajHY+jwIBtTVUPb5Gr7/LHbzNbz9LLZ/3Tu8HMsic5bYuMGj0DKkuPWG3litUUZjsGS4GA2hpKyMV36cO3AxvPwotnPVM7t4OhEzOG0KjC3S8x+3lqG12kwjOEcDQFCGyrLVXy6Xehvbe+1Weu+TNLbscwvKyJT8uCoyL3AM/UQ1daiUI1it4OQVOagNCaEnLyrX33U/PaU/3sqSq3Kx9elgxM3c5e7+6ndvnxChu6XQWltwPQlEetHxSz0+/Uu2871552zJ8Kc7v84WVW/zS1d5TUPYA19sBVVmi7CkBvb0BRagFt5Ygdf8vb+ZS1ekOfPaFO7JCGlrGxKXRwBN4dg3T5gQprc7u6niaoQVGqAG13ykH+Brv1BrV8g5o9hU1stw0tAfungL0jLc7+JoP/Uaf1oUD1gC6oQlPuAKDlVD798r+cv/yn/au/WT/8xfzG55MLN+nJo76hNV90xuYd1ppCUqWTzVfjyTwQBHv/vV/57Mt/vXz5t/tXv9o4+npx8+XUwsVIbndgqNgbzTk8g3pTr0xh5fAVeDIHDEFV17yP2Jd/d/7y1/vX360dvZnbfJxbOEzn1vuGCv6+MZtvQGv2iRVdbH4HnsQEQpEl5OkXvz5/+d3B1adrhzdzGye5hc10bqE/dXtL1+4J60xOqULP4otxJDoYAn9Qcxuxmy++PXv56d7V05XD0/n1rdx8cSg31Zce8UX7bR6/zmyVKFQsfjuWRAJCofff+2I3n396+uLp7tX52sHu3PrKxHwhnRvvSyd7omGbx60xGSWKTtZ7yQoIAZeQx58/OXlxune5u3KwOrsxl52fSE+ko6moN+q3eWxas1asELP4LCwJB4SAasrI8cnz7d2LlZX9wux6dmJuKJWNRdMBX8Rp83RpTZ0SRTuTR8e+vwRfitjjzzaPny3tXsys7E8U1tLZuYHURKgv6fJFzBa3RmPqEHdyWDwSjogAQppLyO1U6GeT2+djS/uDhbW+zFxvKuuKJM3esNbilmm6BGIFncnH40jQVkh9KZVXb8cPnw1tnceL+5GZVf/YbHcyaw4ntZ5wp9UtUnWxxJ1kJg+Fub10VUbO3w7uPe1bPw8s7vnyq46xWXM8qwklOz1hkcnNVXVRRZ04Jg+OJQIA0IelVJ592rv31L1+5ljcNedXDaOzysS4LJgUuMNsk4uqMuJFcgSdB8KQmoDg6vs1d96vYtt/alo/0y7uqaZX5aOzokSWF0oyXWGKyYVTdqFEcgiDB8CSHrVC7pWckZNPlbtPZStnkrm99slV9kiB2Z+l9g4SukPoLjdC2QUWdgLovHr07dvHMnL8KWf7hrl8Ri3skiZWiEMFbP84sjcJd4bBRheg09gkkNfRubdvhgCQyqqa0irY3RvUyhlsdheWW4EMF8ADmZZAsrk73Gh01SmMNQL5Azr3Hpp45yPy7MW/Xlz+7eHhL9e3vplffDmZvxgZ2Y0NFHsCkw5HUmcISDusbI6SgGeDQGUl89nzv7u4/Png4Lv1zU/nF68n8wfDI+v9/YWe3jG7o1+v98k6TGyOHI9ngUCIcl5e/O7i6vv9w883Np8tLJ7lpraHRpdiA5M9gbTdEdHpXR0dBjZHgifQQSB4CXn2/PuLy88PDp9tbJ4vLO7l88tDIzOxgVF/74DdGdDpbdIODZstxOMpYBCsFLFnzz+/uHixf3C5sbG/sLCWz88PD0/096d7eyMOh0erN8s6OtkcPgFPAoEhpeJ/8vzF6cXV7sHh6sbm3GJxIj9VsqR9vQGrw6nRGyQdUjabjSPgQSDQgwe3Lenm2cXZxcHuwfrq+sLcwvTE5Fh6JBGLhfw9bpvDotWppR0iFpuBw6OBIGAJefxs7+RibXt/YXk9P7swlp0cTA1Hov1+X6/NZtdpdDKJlMdkU7B4FAhU9sWePFs9uZjbOZhc3hibW0hmJ/tSw/7ogNPfa7LZlRqdSNzBZrGJODwcBGoqIVfPZo4uJrb3h5bX4zMLkcxkT3K4O9Jv8vSqrY4OjZ4v7qAx2TgcDtoKbihV8tWzscPz1PbBwNJaaHrel53sTg6bw/1ab4/MYm9X6ZhiKYnJQmLxICCoroRcPu0/PA9t7/uX1run5m3jOePgsCrSJ/P2tFtsTLWWLJFimWwYFtcCAj0sIzf+gzPX5p6juGaantNkcsrEkCQca3f72RY7RaXDiSQIJguIwTUCQQ9KyszFjXn/1Li5p1lcU0zPSUcn2hNpbqiP6faRTTacSosQS8AMVgsWV9cKvF9a5fSJfPesY21PNLfGm5xjDU3QBtKkYB+u24/ussGUWlC7pJnBfITG1QBAH1J5w9s7Y6/uMeZXqbk54vAEtj+NDPTBXX6I0QZU6lqEkjo6qwaNu98KKstfx0/wu2fYlV3k7CoyOwcbyoJiQ6DeWIvT39Rlq1doa4WSB1RWFQp37yPy7OLvLw9+vb/x7frip/PTT3JjR8OJ9f7wbK87Y7fEDSpfh8jEYsrxGCYYiCz5Ys/Of3u5//3B5hfrC08X86f5se2RxFIslO9xpx2miE7l6hDq2QwJDkMHt8JLyNPzH8/3Pz/YeLG2eDGX358cWy1Z0r3uuN0U0KrsHSINmyHEoyngVlj1g/dbuPMvz/ZfHqxfrS0ezeXXc6ML6cTkrSXt7rObvFqVRSpUsOk8HIYM+qBkPj1/fb7/+GDjdG1xey6/lBudGU5kBkIJvztoN7t0KkOHUMZicPEYAhgIKSE359dn+8d7G9tri8vzU4Xs6Hg6kbydpO722kxWrVIjFUmYDBYOgwW1ln2xJ2fHZ/vbe+vLawuF+Xx2YmQoHY/Fgr0+t9NqMmhVnRKhgEWn4dBoUCugFLEnZ5tn+0u764XVhezc5NDEyMBQPBgLuvwui92k0SklUiGXSSfh0QhwazliN2eL5/vTe+vZtYX0XH5gYiQ0FPfEQja/S2czdWqVQqmIwaLjcZg2ELAcscdnkyf7YzvryeWFWCEfzI6603FrX9DgcymsJrFGxRULKUwGBosBA4ENpUq+Phs63otvr0WW5nunJ93jo5bUgCESVPlcUquJr1bSJUICk47AoltBreWIXZ1Gj/YCW2ue4rxjJmcaH9YODijDAYnHxbd2sdQKkliIYdKhWHQLsPVDxE68h7vOzVXz8rxxZlKTGZYNDojDQZ6nm2nuoqiVWJEQzqQBsZjG1tYHJZPr4tR0sKdbX1MVF+RTecnoSPtgnB0O0l0ukrkLq1IiREIwg96EwdQBW6tKyNmpYm9Ptr4qXJgX5Cc5YyPMxAA5GCS4XRiTCa5SgIRCAIPegEHXtLaWFbPTE87uLmtthTY/R8lNEkeG3w+GDrS5uiEmI0CpbBYK6+i0Bxj0fUBr5f3bR0oVJ6eknV386ipmbh41mYMPj8AGBsCBAKDb1dzV1aBQ1gqF1XRaFQZ97yPydPe35+s/7M9/tpp/Nj96lhvcGQ4XY9683zbk0EV1MreUb2BRJDgkDdxcVjKf7f3iau3Lg4WXG/nLhbH9ycHV4chszDfea0s49AG9zC7ja9kUIR5JBbe0lZHdry7XXh/MX29MHs6PbuYTC8PhyX7vUK8t6tD5dB1mKU/JpghwKBK4pZyXm93X52tP9uaP1/M7C2NLE4np4Ugm5kv4rUGbzqmTGaV8OYvCwaOIQAD4wXtf7Gbnyfnq6e787lp+ZX50Njc4MRRO991u4Px2nU3boZbyJCwKC4fEgppBH5CTs9Xd3bnV1cn5uZHJicRIOjwQ8/T6rd02bZeuQynlCVlkOg6JAbWUfbGbnd3z1bXd+fnbNjk6OplIpMPRPq+vx2q3a3VamayDx2dRKHgkEtTSXEIe76ycrs7tzueX86OF0cFsIpIK+/u8Dq/VYNOpNB2id02MSSHikDBwS9P9+yVk5nQ1uzs/sjoZL4xEsglfKuzs83T5rWqLrkMj40l4NCYFh0VCQS0N1ffvvUcypwAiLN3Tq0O78wOrk+HZEX824UhFzFGv1mfrtOna3x0QJXwSi4LCIkFAwKMScr2TPFnt35kPr0x6CyOObNyUDOsink6vVWzRcjUdNDEPx6TAcchWUHNNqSwvd0KHq/7NeXdx0jY1YhyLqwdD8rBH5LbyLDqGqoMg5qGZFAgW2XQrcJfysu06WLFtzJkWc/qpEdVYoiMRag95uG4r3aQlKTuwQh6MSW7FIhuALdUlx+pi23iwotmYUy5OSqdGxWMJXjzECntoHivBrEWrOm5nQzMojRhkLbClqoScbcv3VqTrc+3zOV5+hDkWpyVC5JAH57aiTNo2ZQdQyGthUOoxiGpgy50ScrrF2V1mrc4y5idIk8OEkQHsQAgZcLd1WyAmTauy43Y2NI1cg0ZWtTaX5a+TbfLOCnFlDjc3gZ4cQQ7HYQMhcK8H0G1p6dI2KDpuZ0PTyffQiDsfkefLv7iY/eIo92Jj5GohcTAZWRvxzQ7Yx3sNCYcioBfapSwNhyDCw6jgRlj1+0ckz5a+vph9fZi7WR8+mY9v5cKLI77JmH2kxxCzK/xaoUXKUnOIAjyMDG6ClpHim4vCk4OJs/XhnfnEaj5cGPZm+u3JHkPI0dmtFxo7mJ0sAg8PI4KbwCXF7Gbp5rRwvjextzq8Nh+fmwjnhnxDMXvMb/DbFDadUCthSdgENq4NB2oClWSWp0vnZ7MH+7n11ZGF+cRULjI27EvE7CG/wW3vNGmFKilLyCEwsDAMuAl4/171+1X2zwsbexPFtaHpufj4ZCg55Iv22X1+vd2mMGhFnVKmgEWg4GAoUCPgwb33/aW4fjazuDsxvTY8PhdP5UKxtLc3Zu/2G0w2hUorFEtYXBaBjIPBgU3NJeTJ0vxpIb+bG1sdSRcS/dlwIO1z9TlsfoPOqpBphe0SFpNNwGPhMFBTQwl5vJQ7LYzsTCRXh/tm44Fs2JXy2qJ2vc+gtCnEGhFHwiQzCWgcHAJsKstfj5dGTgvJnVzfykhwNu4eD9tSvq4+u8pn6LAp2jUihoRFYBEQOBjwr5D+k0J4e8K3PNxdiFsmwsaUTx21y3z6douCrRFSJEwsk9CGgzWDmmqrqt63pKWew4J7a8K+NGyaTugyYWXSJ43YBB4D26ygqkV4EQvBIICwsCZg04NyXorOgxnLRtZQHFJPxTtHw9KEVxC2sz16ullBVAnRIlYbgwBAw+qBjR8itmQ4KKg3JjqLwx3TceFomJ/wMUN2mttAMCvQKiFcxALTCU0YWB2w8UPEitL9GeF6lr8wxJ2KM0ZD1AEvMWjHuPQIUydUKWwVMpvp+IcYWDWgqazMnC3x9grstQn6wjAlHyeNhPFxLzpkR7j0UFMnUClsamfVM/AP3iGtTXdKyEmRuDODX8li54ZQuThsONQ24AMHbK0uQ7Oxs0EprG1n1tAJVRjYHUBjOWLP8l9fZF7vpx6v9x8vhLYmvYvD9sl+w1CvKuYQ+/Rci5SqYqP5eAgF/MGvfDb55mLsyX7qbL1/dzG4kvfMjNgyMWOyRxmyS1w6rlFK7WRjOHgwAVwPrrp3izydenqeOdtL76/3ry2EFia9uWH7UH9Xf4+qxy6x67jaDmoHC8vGQfDgelCp+J/mz88yB/up9bX+xflQPucdHbLHY8aQX+myScxarlJKFbIwdDwYA/pgcT7N75+ObewnF9ZiU3PBzIQnOWyPxgz+HqXDJtbpuHIJhc9GU3EQNOgR4AOycZYp7qdm1vqzc6GhCW9s2B6IGV09KrNNotZypRIKh40h4aAI0KOyYnaTXzodK+ync6ux4dlgPOeNDNl9MaPDpzLYxQotRyilsFhYIhYCA9Y3lvOSnzrOZHbTQysD8UIwnPX60jZHn9HoVaotEqmWyxNTaCwMFgeBAOvrPyDjx5n0TjqxMhCZDfmyvu603Rw16rwquU3SruGyxVQyE4PCQsDA+royMpk6GYvtpsIr/b7ZgDPrsaRtuqhB4VOJbRKehkOXUPAsDBwLBoDq60oRu85HjzOBnbRnZcAxEzJnvdqkXRE1SnwqgUXK1HBJYiqaiYViwS3A+rJidpX3Ho85t9LW5f6umZB23NOZdIgjBp5HxbJIKGouTkxBsLAgHLgBVF9WzC4nbUcZ02ZKt9Svmg7JxjzCpF0QNrI8SopFgldzUSIqhIEBYMB1wIZyXi7zuqOMajMtK/ZLZ0LtY172oJ0ZNlLcSrxZilJx24RUIAPThAU//IicT0oPM6L1lGCxnz0VZI56KQk7MWTAulUIswSq5gKFlCYG9hEaUgWsLxf/eZ5zkGFvpGgL/ZSpEH7Mi43bkSEjzKOCmCStKm6TiPKIgX2Ahtz9iJxNkffHSRtp7MIAOh9CjvpgAw5I0Ah0q1pMkiYl75GQWsPAVr1DAB+QZ+k3F/Gbg8jpRs/Ooms5Z5keNowPKBM9kqCD79LSjRKCnI3g4lqJ4DpIOWLpm4uBs/3w/rp/baF7Lm+ZGNanY8pYr6THzrPr6DoJXspGsHCtOHBtub88S19exA8PIlvrPcUF11TemhnRD8aUoR6p13G7v1BL8SI2golrxYBry3m5SR+exbf3IkurPe8H3VrTaUNfn7LHL3HYeLezbiVEAQtBxQFRoDpA9Z33W7ihrbPEyl60sNo7MeceztkG0oZgn9Ltl5rtfI2G0SEhcJlICg6IANa1fECWzhKzu5HcSs/IvCues4aH9N6Y0uGTGmx8pZYulBBZTAQB1woD1zaV7sA/GZo7S+R3o2NrPck5V9+ENZA2uGIqq1+itQnkGgZfQmSyEFh8KxRc2/AByZ0mRneig6s9fbOu3qzVkzbY+lQGv1Rp44u1DI6UQGEhMLhWMLiurJg9Tg+dxOO74eiKv2fW5R632lIGQ1Sp9EqlFh5PQ2eICQQWAoEFAoF1ZcXs8dDASSK8E+lZ6XHNum3jVkPaoI6oOnxSoZXH1tApEjyWhYBhgYB3SEnLuh4KHsf92xHncq+t4DZkreqUXh5RirwSjpVP1zCIYgKKiQBjgI3A2gcl5HLYdTho34qalwK6gls5bpMNGoVhFdcrpVsEJDUDIyLCGQggBlj/EbkYMh8mjBs=
*/