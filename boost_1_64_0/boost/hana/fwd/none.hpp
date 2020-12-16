/*!
@file
Forward declares `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_HPP
#define BOOST_HANA_FWD_NONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all of the keys of the structure are false-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_impl : none_impl<S, when<true>> { };

    struct none_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr none_t none{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_HPP

/* none.hpp
t7yzXl+ftvYV5QUkiQWPn3gWH+3AQGnNkYySs5oli0cvs3s+PjipR7takbrMadC64649Or0Vm5W5FZt9aW2nbI/Kndkei5dlqO4lswJGWyJtdP8WNc/yqLKzP+5QnI7OaVHzAdmdFCv66KHt1nyQ58sOcV7QGud5ncV5a4SPjEO4PnpUBzUvabfm3o5F2uiJrWs+/hBwnlBzE9uhF+K1gLJJ+ujJHct1ffQVbTdD6wQBgq2bMaOzBNBHL2hNg3mdZfr2tIADOvntDKoIz7D9XzCa9gS63EBEu8XO38UEg4xBYVsmfoYaroN5Yb6NLW2tO6JZ4Lz1Bzcf+FKStjaZ9ufynJhnOsMsPFPWz8IjOZnBioInG893aNaLlxRjk28XWm2R8x0avBqWTcw8HWTv9tYyOPvx2gkefszyCQ+nySkI5jF44Kgz8MBRA1HBkWHYZZaVZHrozBN2MoMPBWqYl/0Ge1PsMu5TGxlGWhxDM5Fsw3ztiFjWi4+sSZdGNTePr7IKBKOT1RhBtae6UB1qCnL6Fw5MJXOabXAR1Q67xpcu3aUDAcHBvNDEhVhkK0ckSegjLBJ4WfKyEVY8UhSmWxzVZVlpCtkXpSGOQOBI3mt4031/queg8FnGOb0zZeC/iL9rXRba/3JEjJ/kjVf6Kj77BedHYXayjjbJgGDjB6/JzEKoP23Mmsz+bLtO64HDXOnPjLQe1eyCT78r+Pa6Kpf+PCbmNNd2DAqPqp6Ul7txwVeeOoRSQpwUvYzvq+qqr+EcabfX4Qhj9n1ewgkAlbizIDMof+bJnwVhslw30kt1Jjn/0dMG1HiV8SyPpEYqeIbS+3qwyyR6qIe7TreJmZPxzPcPVvOByUfgUUZopJIVQfbYInVj6Wd13XD6ebruAvp5gX501yMUJzNc4YFc2002NpZtm0hkeVxPcwLhJAFXROJwq84p3NRZ2UoRzGS1F8BhEhjlgcQDZFJpvpRwjG0yQkcDJe5zoMyw/3k6ZwOEPEAaSfvxEOv1pD/N0GizZDqX6kl/hGudvppqQ/L3HcDWm9kVWspcVKeATSTIgcx6Djdel+ir3wXfbWDQITHiWM3QHNx42oTredWzOW1tPWDAssq13odfuU+POjJt9KSybI8Atom8BdLeg8ZQyHAOGan3f4GhbvBsJKMwWNBwZx6l6NGgb+ct2Lbb8KoIAqp6EYKslOVemWUoWsENtgELJgnR4wpAVM4Fu0nsMdOzEXnZPdqsT3+PmZchofMyQ5itQI6HZWl5ukviDGJXEZSJiR8UweQd4HmXKPtpAmW3Mm5lOURZCCjeJQBLMJbKE+BIjNNK95u8+/I9gvZBHDRkHJm29k29P0Mj8SVZrQARbLokGo6NoyEayjTM8cAxG3Adt3HL69PWNgEsgaqXlQTxKAexXxgyi9Efw2kJbWchpqQLPYciNL7roE/RGAQgBm/ghYHulk9uwtwFEnNE5eGcVXU3hgDMrQeqH5eo7k9mT93BWDW76SMqQ5FJHIMjkDoPmcm9VxXBkRKbYFoyhTMATuv11CN1rUxdkAhfpZRQh8Yec/Bo8AN7F6MektUpXiGLuDhdllrvWS+lhVOOVHb0WoqIYbyOEEqjeQn1Y64yurPRswdRXy5ixOfxCEQDM3dng2UAgmcGzaAJTBskYrh6QB6SDgBHGayEGGqZElBqLgUyDiLvBmSXvAPOJyG0npiIFMwDUpQNrf/cHZOUCq/DVZtNDIATJQ/sBnDqd3ENpTVJNJbAjI0Dw5wYw3sGPRYxhusYw+Bgk0OMbsqLZ+hmsdccPYdxxn2bdyy9rjNXmGIIyOQiuRDysCswi15tAOmvu2T3T5dtSpc5HQwZcDc=
*/