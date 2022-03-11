/*!
@file
Defines `boost::hana::monadic_fold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MONADIC_FOLD_LEFT_HPP
#define BOOST_HANA_MONADIC_FOLD_LEFT_HPP

#include <boost/hana/fwd/monadic_fold_left.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/fold_right.hpp>
#include <boost/hana/functional/curry.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename Xs, typename State, typename F>
    constexpr decltype(auto) monadic_fold_left_t<M>::operator()(Xs&& xs, State&& state, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using MonadicFoldLeft = BOOST_HANA_DISPATCH_IF(monadic_fold_left_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::monadic_fold_left<M> requires 'M' to be a Monad");

        static_assert(hana::Foldable<S>::value,
        "hana::monadic_fold_left<M>(xs, state, f) requires 'xs' to be Foldable");
    #endif

        return MonadicFoldLeft::template apply<M>(static_cast<Xs&&>(xs),
                                                  static_cast<State&&>(state),
                                                  static_cast<F&&>(f));
    }
    //! @endcond

    //! @cond
    template <typename M>
    template <typename Xs, typename F>
    constexpr decltype(auto) monadic_fold_left_t<M>::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using MonadicFoldLeft = BOOST_HANA_DISPATCH_IF(monadic_fold_left_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::monadic_fold_left<M> requires 'M' to be a Monad");

        static_assert(hana::Foldable<S>::value,
        "hana::monadic_fold_left<M>(xs, f) requires 'xs' to be Foldable");
    #endif

        return MonadicFoldLeft::template apply<M>(static_cast<Xs&&>(xs),
                                                  static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        struct foldlM_helper {
            template <typename F, typename X, typename K, typename Z>
            constexpr decltype(auto) operator()(F&& f, X&& x, K&& k, Z&& z) const {
                return hana::chain(
                    static_cast<F&&>(f)(
                        static_cast<Z&&>(z),
                        static_cast<X&&>(x)
                    ),
                    static_cast<K&&>(k)
                );
            }
        };

        template <typename End, typename M, typename F>
        struct monadic_foldl1_helper {
            F f;
            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const
            { return f(static_cast<X&&>(x), static_cast<Y&&>(y)); }
            template <typename Y>
            constexpr decltype(auto) operator()(End, Y&& y) const
            { return hana::lift<M>(static_cast<Y&&>(y)); }
        };
    }

    template <typename T, bool condition>
    struct monadic_fold_left_impl<T, when<condition>> : default_ {
        // with state
        template <typename M, typename Xs, typename S, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, S&& s, F&& f) {
            return hana::fold_right(
                static_cast<Xs&&>(xs),
                hana::lift<M>,
                hana::curry<3>(hana::partial(
                    detail::foldlM_helper{}, static_cast<F&&>(f)
                ))
            )(static_cast<S&&>(s));
        }

        // without state
        template <typename M, typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            struct end { };
            using G = detail::monadic_foldl1_helper<end, M, typename detail::decay<F>::type>;
            decltype(auto) result = hana::monadic_fold_left<M>(
                static_cast<Xs&&>(xs),
                end{},
                G{static_cast<F&&>(f)}
            );

            static_assert(!std::is_same<
                std::remove_reference_t<decltype(result)>,
                decltype(hana::lift<M>(end{}))
            >{},
            "hana::monadic_fold_left<M>(xs, f) requires 'xs' to be non-empty");
            return result;
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MONADIC_FOLD_LEFT_HPP

/* monadic_fold_left.hpp
x+CUyKMNcxp+szAt5NsAmAAqQ7n+8zbR+7agNwZz4mfLzHGYk8+hb8KceRo0nwXNZwStcvSu5xsrfrjzqqqv7PrxsczOX3/5rZd6hgZ33nrV2aFHHrhmZ+A7O8zZ50V61gv59Ki/+uCeQtgETGv65NK7EfSCLwp6RMvd/8fgP+k73ZyGab1Unp7iW3HVJhoNs0sfBKNYKN5grXPsfmsj5PWLAAfpzVvDoBmOXvsZHeCYiQimIyxl69LiiueWZmub0ROcL3y70ZE0jIgP4J8P74J5wvxGW0/7POENxXzXKVYNtG6KpugCu1471RGDBAfRXV6AWNiXiyI0Nqoo4QzP820d1MPHPgBo4v6F9pn6DdoBfERtQ2M58dTEeVXm9M4q0wqAv+A2zq4yTYAF8AECZKe55HCNGQDMEM458FsLOoTbAxpdVWbw2hpzGuE2xdkCuBD0YAbhHgTMGMBFOM8rcJM+SQB0pgBjAGM18nFdtRlAHoPvrTJ7MKjtidGLVyi7cOwX++LCujsb6o+FEn2QAftjWMN2dF0citX2tfHdpmTvG0mSc0ml3zQAs16/+TrgZcA0wCg1/nVBLr28P5WN9h+1o+QoNY50JTKNjW4kcQsu2eQ9iyrQoncPSFRV+1q0zozx7iHvpYoxmXZP/dsHeJusptkSFKMDCXFRYtm03S7eb0nUOt9K9PRJrqOXXGg9hRV+jRD/zj2XFjTR2pZEdnSAnwoK2ekWn3tfMc1fTDi+RKgrnTcxDas87Y7GwQRUJ3KfKKRETrekSbksX055mXu/jCC2K8LJbDwibx6l4YI+BEjqpOMFPEyYVJS52hrkfU5Dl8qDQuArezsTzoLB5Zrj8nqOynmlugo8hzXB+6uZ/2i8JT4YX1vN/GdZ1aYJ8AECgCBgEGADxgDT6xAPuFOwT8CcAdg11eY4gPhvGv6TG+EP9xjC3Pw3QWGAcaKDtCeBo/jPAt0xog2Ygv80gPzHO6rMG5HfWeQ3N7DFpMs6ave39zWo7wu1FydRxX7DcV8UskMJl7t9b59f2Xe1+R1/EHHs3RH6SE+PhczZj9q7O9ydQHYnEX8O3si3V0kSkCVVj+E7tLmV/KILGnYybbVYtc77z8eiqWS6uZntMszva9hRRCPY1Sr6ZC3db8y7izxuhUeIoTt7u/g7fdk4XH8penxA3Bi7sWbj3PE0XN8RX0Ohe4dPC/fPwwP++Xigg7ZVRmMJrkT/Ht6HEHvtRXlrc/L2MvX3faK/z1ib/t/mm8m+6jnnG3pbZxp5pP5Ow9oALR6kbDxH3/I7Y8Gu+FF7hCXf/N4HaIiVbbn4jrV4jOVOkR9k56ejXrhQv9mW7kxIvE2UgoS0PxGj/PT0SZ6hybMvE9mjeJBmT7e752g2ceBgEl49/C5r8lj2UAiRwiPJYCrZGk4l9+X9d9H3+jD8S+Fe0r3PfcPY7OOl+x7968sOpUv2PYQ5l6UzEld5MMQCTsfzWEd8QvQvkr9pPD3p/vUI+tajNabxWI1pwj4Gu96/BuE/8cj8/YvG03LyjA95nIJ5C/I7e4PIL8n3v435JX6YukHk9zXk1/6UyC/J84p/rZsQDrA/Wf1/5t9JxLUAxL+ES/s4s3D7kF4peXHm08jHjdUl86vmq7nHtm3l5vdtDk+DXzLpYDTVOWoUuOaZ4bfJGb4sbVfndbtOgnR52p2jQ9FIJKpkUM3nZJL436XRlh2mbQmjOC0ZclJJlk+TXVxVfWpTcMcLO0zfZ0S/NGH+ts8r2/ldgNjQ+M3o259FfgEsT0iT9MnjmWxykty3IBwwCJgATAIgvjY3lJRf5fbY5cFkOtPHIn3pt8kYEXYHjR7D6k5kGrBiNIxrUZ/WXeA933KWS80nq83n4WfeUy34q+VMM5ZI15FyJH1SGsA8B6HGWZ+Ie9Ldq3X93v2QlU/a2dQzQCwRlnNXOjtkpK/g578MrFMM9YYSaWvINz+iR3itFBuOxtPRgegRO9Xio4VLgVcTb5yNDnAicsUt1ljs85EC5I8WFKmZikTeQvsRaTKmSFNLb960YsOASOwwnzGJJ/k7avRImNfkkaxtUFA4GqPPSEY4mQbY/P13CGPNSGyY66AGy7BsipNR76WItB1f+ZBCk1UyF+7ynkxZlfxSqp3K9CXVC4P8II22C6Hoyp0QcbN/qUSo3vwtzVzDMX9TM2+Z8FYn/JsclypXrKA8zc2FpSF+ExGIc9zkBPktytnkh0w8irjRcMEmDTNcTUGAerXmJHirE7Hku5OF7UL17hftKIrhK9MshqvB8yR8ZfOgtwmbnSfX3nVWkHR3IqQMMZRC0aOZtBVJ0lDOH5IpT/GYPZBJDohPf2XrI283SqSn70443xOrv7vDnH5OjEu8n/h0tcnvtXWnW+njt2AJ7QW3Q7V+97dI/pKZHLb6sMwMs25pG40safH5XL7/Ni+9hnlo8fI/qmjl/VXR5IMrI+q5B35rJRxKRWIJUKR1L/iTvnihKzY3++cd4x3qpeQYUecOistqlMqX85E5ZFG1x9UrM6xDYURQ75Mvinqn+XV8utrU60BR2pi22v2iAurk21T8IZlYDbXnqsziNnHT8LlozF0H6MG8+Y51Tck9UVkPLrQCB+mf5F3laoPzUldXjz/5EbO+jV44IilE7LrWjRTmwfnWqeGJ5QtpDnC/bhMypfCwSMEiLazyzS6uJaQ+Sf3/R6IdaP1s/ED2/3zvbDjPVeGGeuNFlWskROoAotLFZzGnlmHKJiISqg/OE9/d1etKvJuYJzE3DVlMav+6+fs6I0bma2OJ4lionwtb2YGlv7urSz6J49jpXF3dqY7e81aLv/vzk04GKQkfQCspPSySaEifkuLu5UMevcNo7pgt/S5hh5COyd0n9UOVvKz4gE8sWJB8lFoMneETBKKZrlg0HhHxWyOHQ4lwtIOfMUsKXTHy309UD+W9OS0npsi/Sqs7cWgvBp+0YPELZZenmiE1DwrZKg/EbCiKuwET4AFr3Yb0OqFynNegGTrKahLhzYadjmYjyVqO10aqX5QJofe5IcLfIym+oJvf7yBVKJIAhRoao9GDTDQ4yPfAOLtpw6ErtLw2xHWarjB3EIdJnZCwUBFMRJFAX3aou6sjzXvlzlZ5hraTlSI1v73Db2s7On9FuHyqoRjVnc+skxmLKjF2IJFMUWelfEmdxdFkJDZ81HLqWDwWREp7Ui+FcNX3MNEWQj9L9JVdTouzuoeKaEVUv7Col6g+w7p6qkO6/QR/R7jruv33ha4s8pO4/bJe3LhFfkLBDd0yayv/VhsMF+lPKrpUvh6aJ9PRjLUuGA8lQqn2ZGI4diArntlbpzSTnbKxzifF25t09Z0NclpP83lupp2R+SlMg7XHL6XWm4M06ZPyWCx0Jx0NbyG/Zrj/OmcrCnEz/OGY8TgTtoPKfZ/alpDpSwVnOt/QReVROllchVo4EgAPk0jNqaiCE86lLn1PqUDHqvnojYIfSNe8dLBBJ3rkxORW73K0HlVZhX6urEmxH0w9F2XK8nibjpI2HrJh0/mVNLf7vijXUNE4tqdgFCvqx6SgR7UhhhTJ1wJnOCoFm3xn53XnPOGSGQrToFxYIzxXy3YoDBfDRQmWajWMsR7KEo2WpJkiFIvjkHKdyGIo2LThwGYLc+GmbCKNUSAa2Wzta+3v7t3bukftkLrbVvQlhaEkzFI4IqjYH3JFrZpwSSkkPT+OHGjnGkNIXU+dCZsbh6te6WKLJJzgrapDKXVF1UakluY0tOTGPFGmonBt1GttVH5zmxO3HyOkqtMcAf+UyVbp7/LLB/F5d3VvgPpVSzipB89O4kc9rj1OapRCEhF9iGYOoRDZm3AegAwzmjhQQYuyNMk17tcH6/J1zrrb7t4szhqwD81NW/nEqdJ5dk6oWptIb3qzyhsfpCFxuC12wIlaZ1kcIHp5oWroqUNHxfEbRRlZj8eGMrHh4TrDnQe0YU9HtysrGD5i4RIZIR7sFf1FnaBgAs7JD+D07N2lTiCIM0lu7Wqx67TXfSBCnFNhjSmHA7gCEyGpUp+JHsnwG6ykWSyPfjof7GkMkp5yRGf5weruaO1PMzlwCBFMSonBThwYEG/yxTA2iFMW0cNSn5qkJ9F/82ip5JXUlsdQdflbStTPChTqsqGFsykIS6i+0WhmJBnhc7zOPSmgYdPgIxuEqsN1jInmDal+XHi+idrdSmUTJAQL7SebVpxClV/QrN1Q1+BLa2e1qXDy2EckH2+kZLy3Rl69/uF3XmtR8qV695RLQTnt3t2xz9B19+YOV2ds+fCIhqRwhGI2DX5FZLSzKCSz1g/F6DSMjWKA+FBMdJD54+RDnXffHSL5iCx0KL3+vN64bC10HXluSh0cUbRchy8dYi4/ep+SXszNpklNPDaKFaYrP4wnhNVkSp7ApTzQx21X3hydetnzpbo5xhah/s9jjmAbZ9tOyBo8Ohv512QVk2LM2BeFxJURmi+hyABx48BwQpHjNbZ8N1p9AoXAk0ROC9CpvwoeUT6xhHFRKGF0RYeMnlAKfTEF86hxURb+2bjRmj1g9EVtozecAY8eNrD8NYLJjFz5u1dyxH7HeCGySQ6A1bUd/b+qqQzcseXe6+649pRmZU5886fvXbz7oQ+O2iIXsUxqy/amZuXku4PcYQ1amNhLwCK2fh/c0RRZW3ftIoM+A12CBUT0SB+/xMs7CyX8GxsPs8s58w92F+dvUZMtt0WH7574yU5RiuDON54Nn/3yfXsCn/v+ua+fVrespVy5RLyYfBd1Wpr2Tm7dRmufS1+Hu1RPKH0ovzLpVE+kGvPh11nijqOAvEdJ/MZ6i/1K4Yl3qtQ9SHRH0VoAFfi4mtOBkANCDgg5IOSAkANC7ria7ysACwGLAWcA1gJ2Ao6TLEBQAVgIWAw4A7AWsBNwXMkHg/wYVxBgGlXetLF8MRLxYrXh9RlG5ZRhLj4V9kEAcl45IR8YHQOgNJUzCD8F9ssAkCgqx40Viy+E/QhgB9zTxrLFy2AH43k3wT0JEwS81wN2wz2L+Itg7wdUGSu9ryL+FtgxcXm3I/wZxF8KOzqcdz3cX4JJ+NcCOuB+HfGJ3uWA1XDfZlQt7oP9akAT3H+P8qyCPQ7YCvcJmEsANwIgqla+g/ioYC9GDO9ypP8FpP9+2DFZeRsQ/hTSPw32IQAk9covwlwA+H1AG9yvIT4q0PthwNlw34L022E/BmiE+2+R/grYDwLOg/shmFSfnwRcBPfbiI+e4b0EcKYRQFFWLN4G+2HABQh/Humj4b3DgHPh/jOYVN/XAbrgfgPxK2H/XcD74L4T6Ydh/z1AC9wvI/1zYIdQ5gVTVT4K83TAHwL2wv1r2f4fAixD+T8u2/8KgB/h35Ttj1WktwbuP4aJTum9BoDlQuU/y/b/HcBZcN8s2x8TsRcsWPmSbP8YAANS5ddgUn5vAHTD/TPZ/vsBKw3Tu6BCtD8Wb97zEf4d2f4QQLwb4P4TmFRffwDohPvfZft/FLAG7ttl+38M0Az3j2T7Q1zy1sL9DZhE79OAHrjfle1PcVag/N+S7Y+Z3Yt2qPxr2f5Up/CvvB8m4X8cgHau/Ils/48AUM+Vt8r2vwqAeqj8vmx/rK+8KFflX8Ikep8CXAz3z2X7XwpY5Wr/KwEfQPh3ZftjRe3dCPdXYFJ6nwDsgvs/ZfsPANBulXfL9scA4cVAUflPsv2TgHq4H4dJ9G4C9ML9Xhn+f1Lj/3s1/v+xxv+f0fj/RY3/v6rx/1tl+P9Zjf+/rPH/v2n8/3mN/3+o8f8jGv//sgz/P63x/30a//+Lxv+f0/j/7zT+f1jj//8uw/8vaPz/5xr//4fG/3dp/P+PGv8/pvH/b8rw/7c0/v+Cxv+vavz/WY3//0bj/7/Q+P+/yvD/cxr//6nG/z/V+P8Ojf//QeP/v9L4/1dl+P/bGv8/oPH/v2r8/0ca//9A4/+va/z/izL8/z2N/x/U+P9Njf/v0fj/FY3/n9D4P2eYngpjlaeiYoVnmXGOp8Jc5vEYZ3kqFq30tBprPBUB07PQqPZULKjy1BirPRXWck+lcbanwnum5xojgKybngWIfw3in0Xxq5d5FlP8U1Z6QhR/0PQsovgLqzx+iu9b7llK8Zec6XlSxDeW8Z19Xn4p+RR+h/c0Y5GxBJLRUmOBcTqkpDNYZ4JejyeFQrmpHR6Jhg+5/XnLRfqSv5D/IzHa5g6L6zWGQ3S5ByMUhUtFR+Ufh3yeCsXrVWoUqsdJk4DvikNrJImfitpYzM9JT8R07gGTkbCecbKTPjo6lMSaKeaszSJqEaOSdcL4XoOIPO4az+uzOvniAFrXGYbYSrHCqbBzmNpQV37JMHGlipOGql8VU9W7oH1lLBHB2oMWbg6d4jWsa+Wvbx7lVgt9Win3TkjZl4Tj4/It1l4MuUHAg4BJQE6+zZoE2AuFjEwXfebkI7P18mLS44AxwBOAKUBujbi4NPc+IWyTPE0ZSgJswD2ACcD3AEEMdzcBBjHt5NYXyuyzH/SbTUjT8q0xJxat4W20wNI15lTVGnMMw2yuTlwk+Uq9eCN2JyAAuAcwAcj5xEWY9QAf4CbABOAJwBTgTcAsIEcf0TEN5RrERZw50sLGtPgEhq4pQK5HXKSZuwfmL2G+C3rvob7eE5X4JlfkAuOV+1Fh7yww1r67wCkH2U40inJMoByTK0U5JlavMa31sGNYyS3Nl5uqeOzCYnxjwxrTBEyjTm4DvUHgjF8ozqP0N/nN3YAAYIcEHyAcS2QTo6lQW29Hqz/Dn7ILflbDGpOa8nnA+iaiJR7knQXd2a1rTF+tSDuUzSSHaacK07V9xYGDfI/osVQymg4bw7GDhyJDI8buzg/v6W3f38f5gaO3/UNsH+/0mwvkukz9Fmlrs+s1nEUlcK7WcLwlcGwNZ0kJnBENxyyBcyJRzziqFatK4Fwm6VS49norNJwOiaPonO2yKxyfhrO6BM564CzU/N35obDVGo5eh+S/RMM5UQLH0HAeLYHzdofAUf7xEjivdxTSsUvgvKzhZErgTEscr6tNF7juHib7UxrOJul/qrzTmHlQw2ly0TlV2r+o4VzmonOatN+p4RyR/hWuPN+i4RwrgXO9hjMl/Re4cK7WcMZUO1KYtNsazu0unI9J+6DEWShxHipRz5PperNC3h1Nv9dK9Plb+gSOyuOmiuI+34+03DibS+DsljgqP5dVFKe1PlvPY9P/9PYl4FEVWaNVdW/vS24nnaQTICYICgoYdhcUQkhCIJBIQmRRoOnuJA2ddOhO2H51Oqhsg4rCOKPivgw6+ouIiqMouIGiDAr61FGHQAJpyGYnBFBG/1O3qu+9Qd7Me8/5Xn/fTS331KlTZ6/ueyuGf+E3JgEevWYuakgXrmvCBTDOi8BkA4xBw8MFnB7qGx7n9HfXXSXDUF3InNzvVz/pUJj3a1SY7MKLwwzic1GYI0W/hqH09NXAlBRfHMapgdlWcPG5zueqMBMmXhymVQOzO/fiMN9qYDonXBzmEw3MxryLw7ylgXk8/+Lr+j8AEyzs0/nsntdP6oRrwXyIoddCeQPkBNf3k45cB/Xx/aRa6Kfvqm6EsmRRP2nSU1dJb02EuAjlDii3Ah2Pw7URrsPQzob+I1BGoL174vBedGEd8ycbAUb9j/cgO8il6Dkb22COAdA1hNvV7gCsazHkK7f0kybAFQE6J3RmSNluoC8I/ZVs3dI8VspnTQ2tdofr2EFk9NdK9qLlUPoDEJLfB4X8ZHnF1WOGekP+pb7QUProjfxMWL0/4M2tcody2C+9N8lf0pfLP2zK9yFH9eYs94cpkjBvT/LRn5KnuWt7tUuCYflgFzmfLYFp6CPWFHWpfExAGJXWL5TpY+DqHLmTytF0uAAuuJg9HoHoc/hlchYsPzvnlo8xypfPvgE4X3Vpjbu2XH7GkNUns/dz89nPcrTfW36TfN87+Sb5nLpqf2BFMT2fZSJ7sifex5raO7Qod6v1/PqVKxkv6n2l/EFpue5xyw950EOUlgVDcuZc5K6prHdX+gpCQfnBE2BPYbn8m5F/Sb2vcBL7LRCSc/roQ1mV37O4Rj5HSemLc5Hm8+F8/3Kft4Q+RSmfdyXLJk73dFmC+fWBwHQuy+nBOj/9hTv+rwoGZqlcHJhVUjpUftGKvajho08Yy+e/whh3QH5ErLC0uMhd568ZrnnXFHjvC2lePi3lDyJpQFBtfZ0sL+2zFB56dix/gKmW/s7OjtoAvrE93QxfZX3AHYJ77vrlvXXWQ98B1trPhB7IWw+BfZ7pJ/v8zCX9ZPt7IXiVbG+z8odLdWBbASgPFg6XavN/bX9l9Gz/C+wPAd5MetX2k5wQSLIx29NsbAcf0Al5cgP4CLgW3MHs7OD5ftLGTzIU3NuOsP5/9Z63dhnqhWUqJnCfhvnZ/PGPiUc1Fu9xr9gXP62UEFQi8Q+NMrRMlFB/7IDtmZQp0R7ZR8gA9Iwc+XJkOhyOzKwseuC8lCV/HA4JwV8AYy31k8nxsxN2OBpoOaSRWVlS5r/1sfGj7OOl9G8+mf/mg3/j55effyuG/7tP/CR/QWcwWWwJjt+KT4RdhAOSCisR4dIjSTRCaYXLDnWJ5zdSLxgroTBmBY7BOBFNjCRRlHFIIr0nwZXIcui6oZWBFRUoXMHepy0NuGvqOO4LxzF8xl/Nx/rHKPAOgHdo5nGIdC0uuPrClYlsZABcl8E1CK4rAGYIXMOgng3XCLhGcZx0Dlgf4LSKLNuS22AQvWhQaMtUaLBBvw1oo3RTfkki5YMLrr6/ovdCvlG6XZITuYwDkEs/BJnwCLhGIiMeBddoZf+WmcD8w0Yot/F6NpSdcGnvdzoypNrEDHnflillSLuTMiT6fy46k9j9IxkZUuYlGXL+ui05Q4pc0nv8hEzog4vmpdvgHsrqfT9zAIwfmCFRDmXDvZLLLhh/OdAHl5xrwb0JgzIkmn9EBrH7jw8BmuCiXNwNfZlDAdfU4dIguCbDVQXXWri2wrVvKvN1hD/zRL8zQJp63H/R7xHi+frC6hVhgedxFEbgfjBeJ/L7WIvC8T1HZubCyvh+cXSlf6HA99/hGvcyge853FXBRVQXHVzf5DwcwdrHAf/hKpnC1lZyfYa04KoMaSO0I/kZ0s0QF7YUDZdzvG1FLMfbCuU=
*/