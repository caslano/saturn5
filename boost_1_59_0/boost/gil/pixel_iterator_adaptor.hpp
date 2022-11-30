//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_PIXEL_ITERATOR_ADAPTOR_HPP
#define BOOST_GIL_PIXEL_ITERATOR_ADAPTOR_HPP

#include <boost/gil/concepts.hpp>
#include <boost/gil/pixel_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <iterator>

namespace boost { namespace gil {

/// \defgroup PixelIteratorModelDerefPtr dereference_iterator_adaptor
/// \ingroup PixelIteratorModel
/// \brief An iterator that invokes a provided function object upon dereference. Models: IteratorAdaptorConcept, PixelIteratorConcept

/// \ingroup PixelIteratorModelDerefPtr PixelBasedModel
/// \brief An adaptor over an existing iterator that provides for custom filter on dereferencing the object. Models: IteratorAdaptorConcept, PixelIteratorConcept

template <typename Iterator,    // Models Iterator
          typename DFn>  // Models Returns the result of dereferencing a given iterator of type Iterator
class dereference_iterator_adaptor : public iterator_adaptor<dereference_iterator_adaptor<Iterator,DFn>,
                                                             Iterator,
                                                             typename DFn::value_type,
                                                             typename std::iterator_traits<Iterator>::iterator_category,
                                                             typename DFn::reference,
                                                             use_default> {
    DFn _deref_fn;
public:
    using parent_t = iterator_adaptor<dereference_iterator_adaptor<Iterator,DFn>,
                                    Iterator,
                                    typename DFn::value_type,
                                    typename std::iterator_traits<Iterator>::iterator_category,
                                    typename DFn::reference,
                                    use_default>;
    using reference = typename DFn::result_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using dereference_fn = DFn;

    dereference_iterator_adaptor() {}
    template <typename Iterator1>
    dereference_iterator_adaptor(const dereference_iterator_adaptor<Iterator1,DFn>& dit) : parent_t(dit.base()), _deref_fn(dit._deref_fn) {}
    dereference_iterator_adaptor(Iterator it, DFn deref_fn=DFn()) : parent_t(it), _deref_fn(deref_fn) {}
    template <typename Iterator1, typename DFn1>
    dereference_iterator_adaptor(const dereference_iterator_adaptor<Iterator1,DFn1>& it) : parent_t(it.base()), _deref_fn(it._deref_fn) {}
    /// For some reason operator[] provided by iterator_facade returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d) const { return *(*this+d);}

    // although iterator_adaptor defines these, the default implementation computes distance and compares for zero.
    // it is often faster to just apply the relation operator to the base
    bool    operator> (const dereference_iterator_adaptor& p) const { return this->base_reference()> p.base_reference(); }
    bool    operator< (const dereference_iterator_adaptor& p) const { return this->base_reference()< p.base_reference(); }
    bool    operator>=(const dereference_iterator_adaptor& p) const { return this->base_reference()>=p.base_reference(); }
    bool    operator<=(const dereference_iterator_adaptor& p) const { return this->base_reference()<=p.base_reference(); }
    bool    operator==(const dereference_iterator_adaptor& p) const { return this->base_reference()==p.base_reference(); }
    bool    operator!=(const dereference_iterator_adaptor& p) const { return this->base_reference()!=p.base_reference(); }

    Iterator& base()              { return this->base_reference(); }
    const Iterator& base() const  { return this->base_reference(); }
    const DFn& deref_fn() const { return _deref_fn; }
private:
    template <typename Iterator1, typename DFn1>
    friend class dereference_iterator_adaptor;
    friend class boost::iterator_core_access;

    reference dereference() const { return _deref_fn(*(this->base_reference())); }
};

template <typename I, typename DFn>
struct const_iterator_type<dereference_iterator_adaptor<I,DFn> > {
    using type = dereference_iterator_adaptor<typename const_iterator_type<I>::type,typename DFn::const_t>;
};

template <typename I, typename DFn>
struct iterator_is_mutable<dereference_iterator_adaptor<I, DFn>>
    : std::integral_constant<bool, DFn::is_mutable>
{};


template <typename I, typename DFn>
struct is_iterator_adaptor<dereference_iterator_adaptor<I, DFn>> : std::true_type {};

template <typename I, typename DFn>
struct iterator_adaptor_get_base<dereference_iterator_adaptor<I, DFn>>
{
    using type = I;
};

template <typename I, typename DFn, typename NewBaseIterator>
struct iterator_adaptor_rebind<dereference_iterator_adaptor<I,DFn>,NewBaseIterator> {
    using type = dereference_iterator_adaptor<NewBaseIterator,DFn>;
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename I, typename DFn>
struct color_space_type<dereference_iterator_adaptor<I,DFn> > : public color_space_type<typename DFn::value_type> {};

template <typename I, typename DFn>
struct channel_mapping_type<dereference_iterator_adaptor<I,DFn> > : public channel_mapping_type<typename DFn::value_type> {};

template <typename I, typename DFn>
struct is_planar<dereference_iterator_adaptor<I,DFn> > : public is_planar<typename DFn::value_type> {};

template <typename I, typename DFn>
struct channel_type<dereference_iterator_adaptor<I,DFn> > : public channel_type<typename DFn::value_type> {};


/////////////////////////////
//  MemoryBasedIteratorConcept
/////////////////////////////

template <typename Iterator, typename DFn>
struct byte_to_memunit<dereference_iterator_adaptor<Iterator,DFn> > : public byte_to_memunit<Iterator> {};

template <typename Iterator, typename DFn>
inline typename std::iterator_traits<Iterator>::difference_type
memunit_step(const dereference_iterator_adaptor<Iterator,DFn>& p) {
    return memunit_step(p.base());
}

template <typename Iterator, typename DFn>
inline typename std::iterator_traits<Iterator>::difference_type
memunit_distance(const dereference_iterator_adaptor<Iterator,DFn>& p1,
              const dereference_iterator_adaptor<Iterator,DFn>& p2) {
    return memunit_distance(p1.base(),p2.base());
}

template <typename Iterator, typename DFn>
inline void memunit_advance(dereference_iterator_adaptor<Iterator,DFn>& p,
                         typename std::iterator_traits<Iterator>::difference_type diff) {
    memunit_advance(p.base(), diff);
}

template <typename Iterator, typename DFn>
inline dereference_iterator_adaptor<Iterator,DFn>
memunit_advanced(const dereference_iterator_adaptor<Iterator,DFn>& p,
              typename std::iterator_traits<Iterator>::difference_type diff) {
    return dereference_iterator_adaptor<Iterator,DFn>(memunit_advanced(p.base(), diff), p.deref_fn());
}


template <typename Iterator, typename DFn>
inline
typename std::iterator_traits<dereference_iterator_adaptor<Iterator,DFn> >::reference
memunit_advanced_ref(const dereference_iterator_adaptor<Iterator,DFn>& p,
                  typename std::iterator_traits<Iterator>::difference_type diff) {
    return *memunit_advanced(p, diff);
}

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename Iterator, typename DFn>
struct dynamic_x_step_type<dereference_iterator_adaptor<Iterator,DFn> > {
    using type = dereference_iterator_adaptor<typename dynamic_x_step_type<Iterator>::type,DFn>;
};

/// \brief Returns the type (and creates an instance) of an iterator that invokes the given dereference adaptor upon dereferencing
/// \ingroup PixelIteratorModelDerefPtr
template <typename Iterator, typename Deref>
struct iterator_add_deref {
    BOOST_GIL_CLASS_REQUIRE(Deref, boost::gil, PixelDereferenceAdaptorConcept)

    using type = dereference_iterator_adaptor<Iterator, Deref>;

    static type make(const Iterator& it, const Deref& d) { return type(it,d); }
};

/// \ingroup PixelIteratorModelDerefPtr
/// \brief For dereference iterator adaptors, compose the new function object after the old one
template <typename Iterator, typename PREV_DEREF, typename Deref>
struct iterator_add_deref<dereference_iterator_adaptor<Iterator, PREV_DEREF>,Deref> {
//    BOOST_GIL_CLASS_REQUIRE(Deref, boost::gil, PixelDereferenceAdaptorConcept)

    using type = dereference_iterator_adaptor<Iterator, deref_compose<Deref,PREV_DEREF>>;

    static type make(const dereference_iterator_adaptor<Iterator, PREV_DEREF>& it, const Deref& d) {
        return type(it.base(),deref_compose<Deref,PREV_DEREF>(d,it.deref_fn()));
    }
};

}}  // namespace boost::gil

#endif

/* pixel_iterator_adaptor.hpp
XmLiZatA0vUfGX3MimstgHS620e5qSNAdUwIrfU2ONKMiaPHKIDBh4HeTZ7DaDao3l6ZHK11NwHRycubP3Rd9QmaLquWeEiPvBBYMd7ZJ4BbzTy+L0D+ZZJcCm1lBDAZwRuOk447VijGYaHpCWIGzVlsmvV7MOG9uJyfFM+4Lgjj8F3nGCmK3ecQnyNNSsxq4XcYsoZGOXS15+ogGXV049E4lkp4VpiWKsilnLV1MHFmTLmvVaRiHgVrYNiJCPrZ+AUUoZnU4q4VDRvc3UZdOqg1N3NWS2d3aaMVdwxaM3fI9/SqKMsxaOVlN/clnmrS49b0k0AAlOKZjiHs+2er1hGfJ6qK94NYK+gyqbYwrRrB/AXllgGzvBzBWOeNLKYNxyCSuUzHXtc6IGN1yAb59FxKqJrpGUOmtR80Qx+OvLLD63o6VSa/nznH/UMIVxSH1c2hX8bDHfFVNOOQHfOoboB4mWGIOLxBZCZXoR0S4Az5XXmQJf90ok9HvfjSlKZ2mofe8HFAx8xhvxRaMnxPN7eKXOPqwa+HoEjiaVS7nrnkPX1hzed7Z3CI5eAltMf26MJcDbeOT00B4bRrPEPmHZHdifPJ3dEtuMtW/INvSV++19i2f6J8AjqELgZMKSKRTCEXawGYrYa0VogXJu4tcWrNNL3+w0AB2eIKCT5PQkclT6mtfGFaeQ59p5KI4VaGR2i4gzgDYvdXAIxbEoR//Z+lxnaLVDLQ6PtEhBFBFTWxGvbZbt47wF8BVoil0TIZ5ZFGJb8JlN7pqSQ2j3K8jRCEeh+FRhd7LkE2vB7Sb4mCy2EgEDOYjtaWnuk/Zau5LYwvj38yz7SWnfNeLm9pLsAnSgDt7VJ7DKffhknUBe2jdPjKH9rUOEvjsDcPoUxQRZpUwnnJvysnbxlJrNJKZwE4KETs7cNPiQBST6qNB/37FrHuWOYtclZ/KOVNz1v7PP92yQm8nz2eCKVjASIgkUZxMTnLJxi4PuulPIOYBmhZCgACONmiiKCNZfE386B0m9t9+bYbVRsVrzd6G27xJJ1si/YE5fZ24t8krL5AbrhXETb8M0c5Z16oX0zpv0Q9uIhSsWC1P06sClXBh7826AlRuQa754dsdOz9YB+S8itZ8P5Z72XW5oVWP8JUxsASUfGYi/GXeLGCT7B5Wyw6fd1s24O9T6cLlsn6V9Reqcwiks+MZP9uTNGn6DXV5mZiHGymFeJHp7HZOE+kMGQ0zSUnVmWHErdWLmdCfcA0d6JrM3CFItxx/rFVwuPfnMTAZcbqX9lrTQt3s9Mp107Q/EXrLmKfRKX5r3NY7HK3EDu/ERJthHp/Pu6hyXgZk4EaqPlYHwu6biox43Omi6COCfwZLOCERyDdXzsT9kl5cW9mMNtXAM9LuH670C4swShOCsuWycFUIVzMCKzRrIYmjaJNTPVuIdVmC8+th7gnqnuhu6SooT4GXY0ZOTcXm0FleZ4WfmPwqX9ZVwkY5N+P6Bo7uJ+EnYiNe3OEH9RA902FIvtIrQwhoOfhNz7pe9lIVhyW6AegTEthdVpWLEx0T0anrT92S3u1k8ipl5bdhtG+svOGdXPyvWJyF2QLuNd3ROqeM6E9zD69APwihAKQbx0ijgdbH4z8wiLCPgjSn84W6FI4rU1iJrASXrnHXHpAERLNGN7KEAI8NzSdKvGV4OJA23anmhQozMIpdw5nTqtFXH7oqnGUYIzbRjrzu7wpxFkQ5jW4TvQlZuOE28q9MmQ7iAHY/AD78Zz8hL8kqAzbUOyMml6PT43KgRKRUStwHGMg0BbLEw9kaPL+BBl60Dwe09UnLY3AEEEYXUAdTHUx0Ws+5PRxgDPdPnYEn/7rqLCqFfPiKzfy6aRVwCu2fnhRG/pW+mq7y2Gwtgc2pjPKpNOXYoefjhUI6z2nXIH2B0vhHD1z3J5qzvmNB8D/fBk9c8VJqiMF/qwbZY2Hp76zTJePeOKBSM9DxQ7uz8DdhA+5iXAT/yGOnjUTxkdt1EUQcYd5DAGbKZ5OB0r8E7vd7+GVau8AvbrP4QCpQZzTyDP5cnb18PzvvSdQGeZU3Xyin1aC82K7Be0WbKQk0UfHKqjzz0CYAGMui6JmhKeze7f7KZZDrVnn5ka2azeiKR7IhyCBd+7Esb51vnsDtknnBRbAA2G4frddv288nDcVLYF3UjXgYLNRzMakCnJmDWgZU71KsUt0Db9OcLcxj3BrllmHRQtazXd47UyhTTSe4D58UY7Gp+XY9HQGYeiDl+xyjey4j5f54+VFq4pBHNZ8q8RmdQ9PFApYkH2NtrCkPfCS46PiQuq4sRGWczd+LeeXiuej09uR6/y62lehNMrHNiYr2JEyrnpt6oNPTtVka7O91oSd1HAzvWaDc+Qp65Iy5FtiXtf9HgHQhD18hktIfuIgBA7UlMJn2Nj00BxSHbcgIjEIikNSmC5JYfiFWUxn6BfW8FomKf2WiibWQuOXUYdfv0S4Ls0m64PxA94MChcBUc+cZzn0bj4rc6iOwJEfIOqH7HReZukXMAekhd6V5ob7hkRzYCuvjCfe8tCsW4C1C69OrKOtLstiISIW+NMVcWfcelTeMohhoFALv6XX3cm47cO2MlVpUpfCjpyZ1j/Tgrb7lhrvGbucePUnlVu8wQYbGLxO0rvGc/o4hi6mHR+iHfBof8qSjyY3A2or4xSsTd86JMMhq4ZhO5y6Jc28lAOH2UC68qKG47tpTb56UVjvKLgVcSUTmugmLds1nzUS525LjMVnRpaARuGOWJf7Zp7r8Dyb0c0su6YUW4e3NETWSOno41pcztIHq6BtvrBMT2hGVa4Mi4mK6avXNNRV/wuo2AR84f2ERn43IBtwsDhgKpDs6oEacPeXwBvdzMb3GszhyoHr1uhwh2eLa8+dYZmPwUDkEc8jW0jGQTOUhbEwNJyjBcJQEtDaQ6zumFVsoSZx7SON6UeoIZLU5OYMRM3JnHP15Ij26Z/Bi9FsZnblB/WpUNbp6RONM6pQPXOxYaj+dLDwjzBU+zg5/LPe6tIWcpQ7j83rEwdHvMNuOfdST/BE+JxzI2e35Ql9roFnRizpgyw5zzifXo6ncXATWC8sZGidyAf1ngYTiMzpFm6/Z4g9GnPlnzneY/ucQuunEYbvmBFWGJNJWc2yBFnzzGL8mrHMOE4KJydLndXzRoHkjIA8TyZuryXPbz8JCUcuMG6wyybARKNzlrXImunT/sVbvJoC99wc1MLpKVym220APIkdorMIqe5+wwoCmgd2SJ8FIOld2shxstRoJDqw5SeeiznuUoIBqweHXrfB2HN7Dp1meFOd930VafNlrfUXW9mBFGWn3HvC63tuCCzkurg2kGBhi2xBSM1BGR8hn/up3hGgFZDNwp053AfKR3ihtDa7v0yS+h65Wr6K3AeJLPpaokGSMLquLfqmmkQCZQNZRraR6wLzc/jWqU1if3nIZFCuC6tXAC/julAzvlrkStNDc3KQtHf8s1ja38wHigKz3Tpl7hA4yuUWYCLp2CJ6p7EK3h3pppGvavVeC6jlRKECxmBKPUapgF9n5oWPJexlsLZZLbCiYQEUlUcXertU8XQ0le1TqOBkqf52Gr/nqiGEX/sbYgZok4gdvy05qK4+QkhirazQsgaB8Xl3BMH2rEVKCdcUDyyuvJVbNP+r/4RM51/149Pu6Hz6EzAPBuiiZuIsZjhUBycDEoXOvgIdNYWfVWmmcT9VKkC0Ccc4gP+vJ5biwG4JF4iCruCb0TObe+eFj36QS5sv5kdiVJlJ09IJIXE8i8IRZDlZT6vSGUTbz30fJOYKCLbnIerIbQe1XC2mKuo3k3/CBSj0Yqx/f06ja1nPagF6fEXFhRsqbxez68AZekE9ljs4HhEOcOQaBgxfpHg0ntOyxqAcozZKi3MNjyHQyU/IIcrFWcgjq9c1S4olCOsQeh4Y/rTAhiVe42cf6UuvWPssibiXsTdbxFMQZvSKTD7rXlqhdgbKuN3dGo7ua/VJbIscmIYWExYXcCbj47xrJ9h6QhCgpBLijYTxKdsrNE0jt2TyT48FxJARCFaDbYCVlBovLtexmDmcn79iJd9x8TMNopiaKa+WoFt7E31csbEVj1yPMOzllVOVwTh2Yp42FTPOEdVefGMxRiD2kIlWT2Yxp08OEh40MvtNAbWR0Si5tlFFGCzWOwqfeoldEGRmJK5OfsC2XIG8f4NlYVoRxiYbn+bvLYefJbbw2w27GknzWQPMs/s9jadYSeRnNDhjPyyzTqcw1V48BM9k4LTkPIINZIi4CD4Nr0GLXB7HoM05fCb6wnGzBeCTRVL2GL3hOv+7xjJ1fNw/n77H2bd40yKOyISB1r79SFu7wJw3aEM2ZiTv4GNfYdvN6Dt7n5hSJHhE7Km/DuYws17EiNRQkO/5Sy0pnzwE8sb9kXJkEH88c1cRomLjudM9VisLRC5qF8ZqtwVyRzxIph1KuP5QPNfQ4Ym7GXNoY5bNuAFhZf6DN8KwInLPhuq8ihnDRwNa1FjcxIJ+nA+C1KjX42WJzUpokzOc84/xZxZoTzdvUrAzPH+OOLbjFSmuQE3A1Cs+XFJvBoKv1fjbXh+2j6XsrwPPi6jYkdye7M22mLHO8Zr6nX5qW3Bq3n4kPweEPZFaYqyeNOKuzUfaa7YX4h/ZwBI/PSWQGiud7HXubVfdw5NDz6q3caQL/wMt1EIthSimVqkDti+eGl37b6EsCQoirSOzwRBaP1Ps6XvilDDeOnhhp8rL2DGKxK1cvs82WrJ55cWgg8yIxrmQ8pD7MFDzhZ8RC+Hw3tUwYJhFXGhGLD4p5W6Lv5RGZee3HzBPYecJpx6i2AzFBJNjf3bmA2ZxcIJQEGJHMrxnd4fMTb7wLObYWrrHz8ab6R8DSnTrIUoXSbxaVB41BptvxtoEK9+BL9CCEgj11wATGTHQpu5WqNXivPdymgqy7Ton4ro6/FyeKzNbG3T05gpL4AYGzdhMbwgyVC+40FeIX6eMts5iUwl7JiHRcSA8/7zxbj/JDXjfZA07rszXnuUt6jszI64ELnqm+lxJ8ar09xv4aKokDHmSBjq5LPiOdNdZTC6bw4kVXxYubs2scTGzERgRV+ulcbEo+WqtCWcQPWO45VovG0H7RJ91ZMpWoclr7+x7yBWyLz0yAmdE6iaxoNiFV1M5t3PcDETdmCjHSG/X1mhxXzAjGdjhFPTJ8ZSX5XFwWbGq02Rmrt7ks9bt+ynuMGBI8gWnBx505quRRZ3DjaBUKC2ibSiIJv55/lvdNd9V4CkxjFZKYaDOEWU6yKI3kgCZFlJfwb1QL+bZn1VCpviyWo2ihbhDjX8YB1XMVPPOoksCpWTMH0pT25NGYT48tLXob9HrzI/KqWRU65xzS55m49O/f/IsiuzMUI15Oc8ebiIkqU7LD+VO7VK9EUsiapOLIAyQbIlVnKG/FkoBp36IRBmccqo731H3QPlcHPPMJj7/t6k8F0l2bai6z4r/XI6m9PrE/yZoDG/WLS6f74r6tgO8Q3srXO92QO4D1nuJaXBj0gonvDPow4tmc3Bz99g7btZico4gVB/YbpfiYpHfTLqGRUnDhuGCTPLg+CZoOC15yJlzkA/khrY8FyzAlYL+1PaTTYjo75DxUObfIbB+8cNn1euwpYOviQfRH7ZvFxS5QzA4PB+cNGsO3hZmaRegcHtVBsRy7pnYqE+toPIGZk9FkucUEARXhRT8rJ2RC6kP2AoPHEPbebkiWYfJS2xzkKcDBA5f7fW7dtj1qGEr3wm0J4E+/PaoW2vCej/yKtrO/OeuSdPuI7Sz6IWsOqrZaxm96iGaA8FBIj8y+gpyfqfiM+nqM0enJHxEtE7YsAPWqQ1URt/QyZePLcrbixPwWdEGFuF0TfTUGNzi5R5tUQ9xHueuWzKFI+EZhuqgFw+N2bC5b61cjGF39Fuws4AsDwRS/VyfvXRK2X+Q4pXitlzK47FogIcm/2aUnyk8yPmWe6YVtLq6U73C07+6fF9ZLw9uowd7IVOd/R7zm2fXK1s3fgyT5EU/hidCyXj8etFVSZBU1SRvQ9aBtTRs9UW+YbxY5dZnxY+chj7wuaCiE4qsWpS0CSa9Vx/BQGFOeAB2UHaw/Jl7WjWXOt84j4VTHFSUdZW7ErnqYjgukGh6kEtoVq4GXv7Y8BGrnbXREL6MmNM/+t1qFICjxIg+TYaS5g1Pw0+xhq0hb7+trUAdveHYf7Eu5e+WHL5MS3cWEpFhWVu1jkmw/3DGbnCPZe+/xyepb8AUMJeaFgimI3S26P75IFGjVqyNtB5SNpk63Drs+uZVzprzjq1JmJgiwuTStWwEyb7IMPbLDJRLVa860NJzudoGEdVny9buc++jIogVJ8oQ5AOLgcnSu2uCScbk1+RxXHtoIFLj/ax2yANWKuE1+Pg8gTCdVR21vku4a0lLFy6+kPV47PagUBdewVA7rjBQCkpGMkIk+llAoUwimeTkaVSCQuxTkHCpWpI+H8JkHdioDG7yccpkopLOc1CFoAMxkNaoWjBzTFfNH2rR5unswnkbXY99QurBv8Hr6foAACCLqcPpkCnCgnOPZ18aUxNfA+azSQsn1mLQ8GwGUST+5FUzGiikjaKED/z6+fnxXwQACPgV+CvoV/CvkF+hv8J+hf+K+BX5K+pX9K+YX7G/4n7F/0r4lfgr6Vfyr5Rfqb/SfqX/yviV+SvrV/avnF+5v/J+5f8q+FX4q+hX8a+SX6W/yn6V/6r4Vfmr6lf1r5pftb/qftX/avjV+KvpV/Ovll+tv9p+tf/q+NX5q+tX96+eX72/+n71/xr4Nfhr6Nfwr5Ffo7/Gfo3/mvg1+Wvq1/SvmV+zv+Z+zf9a+LX4a+nX8q+VX6u/1n6t/9r4tflr69f2r51fu7/2fu3/Ovh1+Ovo1/Gvk1+nv85+nf+6+HX56+rX9a+bX7e/7n7d/3r49fjr6dfzr5dfr7/efr3/+vj1+evr1/cvgKXf/e/dZx5z29iScwvyCLYJhwgLAkAGG1yquLc8WiJtBOr4hzOxlsy3jP3p8Pe6pTLUkXrx+tzSWZLlHmUfze8r7CviApdVVJyyI+cU4/WTtS/VIbTC1Cr/m5VMKvR2FHXmheCg99qPbC04h1iH2F7aSs7TUE9SDyZYDGz68e8RNGUBsSlqTaNntCxgZ9TSZExmTcZPBnRiUW2MdxwHCvINOT8WqSZehWh1Z50sGMq13OU1ntOu4M6U39463oxhhFJavW7crcHFVBbzyPBSJZkDXBsBbbMVj0CHv3LwhLpuf+FASPMrQru/JpRudJLiyO7BD+GE7FxDTZppiAqFmyBMDMhHp5EKXnMbS9NdXyw3u9yGhEXP7wt0qGEadGrIyeg7H3PzCi+22onylvsvL4QAHwqeeNp4YQdySRdwN2WHRAfUpgX2FOEKdeMb1i4uzjtPi6t2jfHORdHUQnKdcZBFuEXkRTsqFxXnw4Ix3DuZ9RBLu3HShbHOHC9kD7tOvbDb04ZbtzkfcrZ2284+Xih8p2R+TGGFtYaURc0mticdfYZLis2qzaPdGYtUs49VqjHDG6gqSEhrCH4B/nGm2+Pu3E/sO7zokv64PjYcQ6igoI4TXJeIjgHz
*/