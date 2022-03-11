/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SEPARATE_INTERVAL_SET_HPP_JOFA_080608
#define BOOST_ICL_SEPARATE_INTERVAL_SET_HPP_JOFA_080608

#include <boost/assert.hpp>
#include <boost/icl/type_traits/is_interval_separator.hpp>
#include <boost/icl/interval_base_set.hpp>
#include <boost/icl/interval_set.hpp>

namespace boost{namespace icl
{

/** \brief Implements a set as a set of intervals - leaving adjoining intervals separate */
template 
<
    typename                         DomainT, 
    ICL_COMPARE                      Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC                        Alloc    = std::allocator
> 
class separate_interval_set: 
    public interval_base_set<separate_interval_set<DomainT,Compare,Interval,Alloc>,
                             DomainT,Compare,Interval,Alloc>
{
public:
    typedef separate_interval_set<DomainT,Compare,Interval,Alloc> type;

    typedef interval_base_set<type,DomainT,Compare,Interval,Alloc> base_type;

    typedef type overloadable_type;
    typedef type key_object_type;

    typedef interval_set<DomainT,Compare,Interval,Alloc> joint_type;

    /// The domain type of the set
    typedef DomainT   domain_type;
    /// The codomaintype is the same as domain_type
    typedef DomainT   codomain_type;

    /// The element type of the set
    typedef DomainT   element_type;
    /// The interval type of the set
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;
    /// The segment type of the set
    typedef interval_type   segment_type;

    /// Comparison functor for domain values
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    /// Comparison functor for intervals
    typedef exclusive_less_than<interval_type> interval_compare;

    /// Comparison functor for keys
    typedef exclusive_less_than<interval_type> key_compare;

    /// The allocator type of the set
    typedef Alloc<interval_type> allocator_type;

    /// allocator type of the corresponding element set
    typedef Alloc<DomainT> domain_allocator_type;

    /// The corresponding atomized type representing this interval container of elements
    typedef typename base_type::atomized_type atomized_type;

    /// Container type for the implementation 
    typedef typename base_type::ImplSetT ImplSetT;

    /// key type of the implementing container
    typedef typename ImplSetT::key_type   key_type;
    /// data type of the implementing container
    typedef typename ImplSetT::value_type data_type;
    /// value type of the implementing container
    typedef typename ImplSetT::value_type value_type;

    /// iterator for iteration over intervals
    typedef typename ImplSetT::iterator iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplSetT::const_iterator const_iterator;

    enum { fineness = 2 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    separate_interval_set(): base_type() {}
    /// Copy constructor
    separate_interval_set(const separate_interval_set& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    separate_interval_set
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { 
        this->assign(src); 
    }

    /// Constructor for a single element
    explicit separate_interval_set(const domain_type& elem): base_type() { this->add(elem); }
    /// Constructor for a single interval
    explicit separate_interval_set(const interval_type& itv): base_type() { this->add(itv); }

    /// Assignment from a base interval_set.
    template<class SubType>
    void assign(const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    {
        this->clear();
        this->_set.insert(src.begin(), src.end());
    }

    /// Assignment operator for base type
    template<class SubType>
    separate_interval_set& operator =
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { 
        this->assign(src); 
        return *this; 
    }

#   ifndef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
    //==========================================================================
    //= Move semantics
    //==========================================================================

    /// Move constructor
    separate_interval_set(separate_interval_set&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    separate_interval_set& operator = (separate_interval_set src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }
    //==========================================================================
#   else

    /// Assignment operator
    separate_interval_set& operator = (const separate_interval_set& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_set<separate_interval_set<DomainT,Compare,Interval,Alloc>, 
                                                DomainT,Compare,Interval,Alloc>;

    iterator handle_inserted(iterator inserted_)
    { 
        return inserted_; 
    }

    iterator add_over(const interval_type& addend, iterator last_)
    {
        return segmental::join_under(*this, addend, last_);
    }

    iterator add_over(const interval_type& addend)
    {
        return segmental::join_under(*this, addend);
    }

} ;



//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_set<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_set<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_container<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_separator<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_separator<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{
    static std::string apply()
    { return "se_itv_set<"+ type_to_string<DomainT>::apply() +">"; }
};

}} // namespace icl boost

#endif



/* separate_interval_set.hpp
lUPLMELCQPSwIM/2/dspAm5W214b6vVYugRXLDxn2U/JjC33T2LV+gBooPAlcda4FMBczAs7UVb24/IRtRyiDJdVnwSB82Z1N0FjV2/s8rWp/n4n1xockv7JydMk2LbCWlnS/bCfq8wOiCBXt6WOyu23LgX8dzjgPg5i2TlsG/pU18EZRzE4mss/Y4RmULaz+tGbs+rEzN/FmTtjk32H70W1otNlRODn2YZVfhrHTL0DNsTu50Bi/lLUk9+1aGkcR12vphcNRrKhPsEE+OGRX98Gy+7nAuYsseYeAsVD8Fl6jlU/CY79wTR+GEtQiwk6CJQYjIU5zBMO/oL8f10KcISECRxXUGyO3Nt0GWU6y0GxUfTfp7sJYpqQM2Cx9I3c5pnOIQzvweQxMIxI4SBuX/1RBq9wEMPM2Fw7HmMs7RoxPDLzAXHL7i5zVe38fojZP7rrtUfPCs7QVRSVm03PY3uGdBEP/KN18n3+3sLb8eely+hcPbb8NBFVca7ggGM5m9vNQWlJ/sN3WSmKphBy6VbMb+WFiO2x35/MfiePX6+TI/JTK3i+JJNfIRJ0AObl0q0crk0fRFsz+rlylVC8Xxsdd7xMWUtdv0ekxiG5mgxDrF6+o0+o+NP3z73+Pr9lmuEuMuvy1JnncmlmAnvpX64nXHWDDwXaG9ipfkGJAl9THvcPZIxrEkCMdTTCeoKa/gtXFuBagb6cPkEIgPD2zAas/3FrDB1HZqjQ5pIRymEWZljOi0oTzlG8hPM9pbc6E79g9gC5n+DmNr8VLE4MyPoYqmv/0pt4DEfr8ov+PGfVPGJqF6YWCoJfd4Bwbr2KBAAIf03jS29hbz4I9+wOo3T4tGfGO1ZiUKlhzO2ka9z7A+NdVWQliILgEH4+rhRdrPUyPDiyYWwTo7y5lonwOORQgmiaJjk/FXIDVqCQ5ndBubeMSW9iIdFOFRsjEv5rSnY94M/1gYAoKJAOl0VWHI/qmSUv6waIpyQGqT5XgYRKO/86Xdd772OGqYs1dXVWYLYGYPdnn4Mek4GW0cRYRguoMi/GCEMhVmPiw+4wpVaoHfJEU5sFITx5hGMTA6LoQU5uQU+2gsYTnRpBM3jqLBdvYtj9KihmvfiHocpgJitoTBcJRrf5HWNw1lej/REIfoYvf61Sn5lxKIGYyZXitHxEUg6QLrnXl0FFsD6WcetD/Q5U/Iirv8n5M46BUecZ/1tzYuc+NT8VtHFhN2/+lsv5+N8chAkwrl7NCEU2ROIsCKu0EdHy5Vhj8wVTs5dYxFSeGCe/f4+sHRKBuugt8w4Mi9nqOB7irWAOvq3k6IhzAxIqCl03ejN6LwAARWwxHpkjrlZF2WibdgxdGMfvqDbRQ20eR4PiBIDQLfIKNtyfEYPmAAkUg4aPsn7xckGHwKBukkW5o9bHwbT7NCm+fJzudvO0F0uSF+ujNZDPjJVTc9j4O8Ofj65cW/UkcU58njfBw7eOlEBQo/TsOYMYjd3mpWGwgRz/xjcchncxDl+FKqdunFwhCx9aZ/OtXF/oHdU7xL95b38yUkVRaDa4VSE2mNg6Rc6/KDCvG5oJC5hiks1AQ9QYV2Dqz4lDgqT2IdydXvSUJbXn+hb/UTjvFEmiXUQ7XSXCpm88jqfg0xCJ1P9cxE8MJzcfMr0xtMSohi89qWdt/5U79Tho9ulN3rytjpPeOG9WqTDhqqaV2/UzFd/9wr7Rn/6wyCQhzswFrfPB74DB1muCS1UHVIGhkxxfT45RW3uEIDeyissN/EoX89wEC4LCGG+z6sAkCz2Au0mK2JkCrgGW8c20kkeMokKKX4PNBzv/6uHp4KPUyEsLZi1lKlrLGsV/QQ/E5Tqch3v9zIwzXG6ufGKhzcVij96V955/AxjXOiSgxtEW6eQx8jqHL1WXz428ZuGh0WtfiuM/hidjk2Yx9i3NyK0uzoOpb+prT6lQXUJlCHepjR3+PqgQn5wlFyH7ivBA+jvsk8y6+j0jR71XU/Xl2hKtqZ7I6nubLzAvw5argNNnLgKrfUpKBP7JtYI+ERyEEWcqZza/J6XpJsv4zZwlA+KkhR9/lqpLdhCEDCdmWkrKuIHCr6kCnbKKh3WeYeBjcVeQsHsaIGWZZZfDQt5K7hVxPEuFKlHRpDnlVJVprKVtq2XB/TjBTeid3M0/zbC6MqP54Q9H/jP2HWkoAhF+IdgBXapNi7idldO3iJ8cnj77vYSR3xYIrgvU8FHu5HqP+rBvNj0mvqfhbRaKrqtS2h2xAnPGRq2b30FrWne4nLscmUtJDzgk9gpqReWvk2s5Z9nYdoOND8jGTeiQZ7DruS7GKQU1ygXf1KTFWC+D/4b/0vNx2pK5av0ckaEcC9U0HQQcuVHylW5ZV8bMMxaQysy526EH5WX/vTVlg6z+vr2E6KN97k+9Jzo/Jl0ZyKf9DYgsSapzCnaQZMmTLO63d/+q8+4atWMPomkKvTpfuxlBQdexKcJV+F1ODpVONhTHf46fGPZgUXYWQ0N8vUrm7zOXE0B/MUHJYYTdRgGzrb6VF8+d5JX+KZ6ikmc7Sg3zTwFESRsezcqWya68YuMT0RT5WETO5afjDnuqjHtmkpuhWD8UQM8cRq/6FMxUyGjUgnUhatdD45xCqC6lFWLyQAtUNg/Llvm9VEute0LM8FkTSRu3PoKbnUhWLgSUtvHHRhUuEyIDWik9XdHrCl4whmjOX4fJ2EN4f7QpByPopPPqBh1ZaMQn4EXk1Q82VCn0I/4TwTEsNCfYpTk5YyRiVKCNwb+nNY8ZQaK6rmIidE1mS9j/bvchO1kn4tiqfodmyRPEDMX3LM+7iZpW/4d7Zk46OTZI1j5zU/2rUgGtMB9WJ//n5yXrZ9s7TKKAVRqisqxKDD31hI6LD08mjME8IUgQY2Pedg2itP9IKs4olfJNhYUEzXK7/g+aSZ5m4POa91Y8fr63QH58BkRGi8rapJ9ERiU0Lm37blco2d3HJRzA65eybef9bqgphrs5fhf6LN7WVXK/PiC14FQxS4qIHKXSDSv4XNMbV6YtFuuG+ebK+Dw79PJOVdiAqlSoQ7bLNi/rIqnYN52WhhxuhdhFQMKRFOyVq5+jos83X2KAmmLMNhZUVoM+JoN2k0XGw2c61bdKT/EqdEw/BGNGeHb3nbUjohJN2lXxKLERmDMPsBRvpJR5zF8xohwBHjPxf9kLYWjmKEdpJG9zc88OyA429uULB73aJgVGgOkCel/J2nTjBZASjkx0B0pQKXgqlyI08RBSAbF0iB7u+4Tq8Z02+MTbCu8r9FCQEt8XJCh70SwzyrFgzhIyE+ieOis/P88oo0XkMJekQnFw5lBkHxC8xdAxRvpjT7wzbT50bsEM4NGbtuRouSi+pr4Y9L1GCUTIxbpy61Il1FKOOufjyXzNbaSzwbCtcKQkRUghiubYe9EUj7tDXpxx5G9RTt61MbFTXXbnDmyyLq9/1IVuO5f1OK4E5ADdUQErGwAAxt5oOApTZ3e/P4elVYbNfn6+XKsOiy4qz4vuDn6+n3dpAACAgXsaaWyb5Boh1K2ycXg06vcI0ZVt1sODCMOG91YKBitDgHkfUIMM46OG4onlJysE+RPP0Du2ZNjyr57t/Q90DQ3aJgXSRFuv9/8y4rfDhyWJ5G1Mn9rHCv91ztNfY4gEA2+42Jq17fmIHxjhqvxbOats8KfysYTVRuJwy3c5q8A+8kf3SmLDMKhHw1Mz74Q0xSFFe+nn0u+R53PxPaZ3PSzaIfsCtUyNJlyQ3XYCHmFz20n+wW8SIhu4eoYlSyiPZwegsyGf6k9m7BAiRMfgtnmKawkKcuUwwwRjj9+d2yj1Xzs0faEa2KNJlsfkMQM4Hb6Ue/Iy1iGPzpoIDe4ODfALXdOxk6DtnSVv2VZM86Lg+GxZXDJovNkuZkaNsEdcvenlvfsg9daFxO5qHV1k5V4Ae9I/3jHqTXf/BE8b10GFPs0MyoMw+w3/lUi10qaTBJTKas0SYinrjCYOIQYKOWG5QFep+m/vl/wNZX4jzYLgA19/IuSBwS4CEuKmFnu8HKIN+rMKmoIksuDw1pKCAMWe9xeCLVMyGotsv39IHIGDM+21tb5lxftET93XmxzthGO21s1Oby7v24IaLKtBl/2bNd1blPBUDcaKU5Wph3hvfJsLeOrJjaILT3iRC3Q0KLgS06FS0AgtRal1sbhRHWnt2n49ly47wPqijDHmH+B27hgcTtZrgtwsQuQgFJQrpbEJ7EHGOt3bgAA6p+rUKJFe20mhHmfe3Gsv4dDJF0SWN2GwMEC8oD60eTe9GLB0AozZvQRAGfxOiwdSoEi7c1Dt+oPfyj+n9TUSBvFJKq7D91Bl+G0WoqGYhYMhI1FjL7QaWy42IaHJ899WqI4O28aNx+m0cPLBukBu7DdTCnf7rw1/w+o4TuTp4fysMNyAxATTrsT/FklA2WVwqFbhtZ4bnuWfRYu0vRL8H347C3EAAAgjwUwgxAbXn/8+PlDwQwv12+C/s+b0xWvGpVy1/66XNTKRBcUSmEDm/Wffb9Mw7bEiMPJw+Cf+M/jPn3yWKMj5Qwud8OuRB9t7yMMeMaFi5w6hhKGUbpNLOlPrRPiK8Y7OLVcWZtByxkSCrt2JKT1QMs1WptT9iEMWb/LglaEARcI8G99BRWCblxLgVsmU3tg98TcJ9+c/naRSz+mKrj7+1BcXQ/Qa6BHLZHSqfNFp8hzs75K3+q2Dhygq1+eac2qQq/SpsCExolftDkObJ7eVj2VHUDfepQddAbyx97bywXCWpmG1O4rAdYeAd+yWfqOJF2KXBeFpqHI5TxCg8FNI4WAC/R6eatMZIQwl/gBMUci6G7RlCs98NuDMOLJDGRgVrBIupK90wwpcnyK9dlZmGjYd3m7oTYy9oqhAg+MGRI/CLleF7an1f9PHla73l5slF2gpbJKHzPvqNh+RK6MQM5WIQZWrDgw4Urgrxa/J4unxm5H+qHWg/pAxhbCn7SYe5ZwUJmgNR9eklEpt5PU6oipB4lQObLsCzaRM2kr1TexvLiX0/X239zIoPfJtXsJ1RWaBiN1wYHB3q4UjBcS+Dk0Jq5BeW4dRAPUNIOfqQZepMoBQBawZmNDMvKTqExktEyQ0S08emVz5lhPtBtEWckq43hNxD/txk00twrKlxwVKwfeywx6EIKEc8fVWfQvrK4IxemWloRsdhF/+c0wWWkiI0NIHxbLK4EoavExEQwNcRQbnLCCnNnWjefaSwRRS0QXDzTftBduBYIqb7Y4NbCfidxOqDbBYmvxFClYFar6Bu1BNQZ6IY9fClayQzyM0d1iCKXA4QP64pFf3voRxBIb9LaBVKBpA5imKkh1aP1Ed0vG2WYAWJBtSYDYBaD43SwyhqzjcnVjZzWs4YjhMSxvKxUqMn/NdAMqKwY2QNTDDIDe2xLUNsBctZ+aWq1O1nu3ssUBXInIZBgBjho52LZGcduQlsC/3ueq80+8dtFYuHiQEL1CPGVPVeyIB+DdZteaGq9mo+wEDqeDrBfp4l8u6uTu6V/Y29n6NDH0xHnavwMcaEblAH6iHEgN5+NabXriEL+oTSzoS1zvr9u32TAWxJfE6amDkHsZzqV9fjUw3lLlLouW0/d/TxNKLedL4DeIm2GFYvQxmbzqm1+yiZi5ZhgLibTBjhW+inp9zrM7W5fyrwuCYX+LIq4rnoDQWv+qrvD1r7r8+C23lvUM0rhx2cVx5/sK0GO+YMAC7XN9yeXiDXLcnxPY6ZzTiw8cVbwQquipcD3DBaCB9HVH1HhO2aaFoddLUyi3TdSt72Hsz4vlFETvM10smQP6JU5QatUQgJYSWVBVGreuHtRIbtqj9dUfumfXnr9WFFtru6JJep8O10XTypf7HPHUZJA6PiNN4IAwgc9LWm6H+qeMIIjGl5XwemUILuz5VfNEFAdGihU9AlplH70VmfOTBuw3HXnPR2Ts9LGtz3bqaJuclu7/6nEq+WSCPaipL7apoeR3ZRWvolZlL6c0urRqqkuGPcLMuiU16kcx2Kb6qb1BFrP3lR9dV8aH1zTg36+ETrLYQXuqlnj5lsWmFE+Xunuak7lhNYMW11KVCsJBDrOVYV8l6GkKhC9ai3GODCwRybHrFGTQgFTh6gzmPoOFPgwBi7Fs+Kobbo3NVMeq2SIYZBsf8r3dji0Uj+O2OzKJg0j3yKUwnMTGqKtneEAk86QigvqDTPTrYhEYILRiL7JuiCsneJlpHmurrfxF3E0+ur1SAu5P0uul4qIvaOmxPZg/ZdNj3WhR0lyUm7UOrtWyWkXxdqeCVq3m8qUJaxAjccu4L6X74lgeaNckJ+rcDtbyklEofGNEPHXxRfDluf8iH6FRQGrZUXyVnn4e0lofBuqXS5tqioBiHVqhvdT9A3kDTaKS/TTkX1hfu0sH3r2zkNaO790loPLky9xnIRTNBYDqJRcaxLhgZYQHw2Wv0rfhjF9iWSW7qKnH5HHvnp0UwLi8A/8rvMncYAIcWhGX6nL6B81Ccmrzy0CXxf9cyPpV0/sVmAp1BIQs8xDd3hF+IuU1hdrC/dZeTZkRTJinnuwz9UobKsxWFebcncR6obF5LfFc+zyO4Yh3y529XwJDh/LFpaowJNramyaowfgLQqKR/iRnXOWAVy8+KAEUgoVuxEZ1zkM1qbUycDzsuEl9HunfQSKOU9zQ6/xcYX4REQf+pCs3LPrTPf9DaSLm2RH1A3YEuKOhHyKF7dmvoOV9VZZFDM+eyh3AhqBMXuW2KyVTfte9UhS4K5AzKni0q0HPxouQQqjOQdOIab5Ls9QLwpGzsvg7uw/CN1sHucHAA50h92JmtINn2hqN3yfEiHEpU7K1ygv33pJv+Hoh3H6t95a1ey5kAqP7Hc2c3xGx62EJLDSPUOlt+mBFWbT95uaIMmfbqpLkeffOabGaBSpgE1lqKjCyzsl+5CTGcEoy08/h7nT9sHvAQuVwW0oob87xRT+bDw/x7ESIz8r3pxzCQiaToiNqluPRJRZXa1X5231LdZTqLmutFfE+8Q0w00P0DinORn8zVSJrJnYaHkya62vKoFAyYlLeNdiELE1GA9aO7zcRDwxu6a3AfdEv5ZvOvaEyQMRY0jr/ydsV6/AU4NqdKKa1h7AkmpigMQlyeh0vfuGhfSFQi9JSxKKiXASEK3An2PyxHGdzIAv6RsjcJbiyiCVuSBgXQzXNcbvezaH2VYUYvOiajLLAXildesEai9dKQZs1jxQt7ZHko06CVWHYGu28qut47QuWosoCmUAwwIIe3ZE9LUX+VYSOvKTI33BfmiU9EjPF9tXN2nr5snKLTWOjpRAVHjFUk0dMEDtnhPgjwbkKMJZ+V+AFBiBltYAnqNSeyeJNsqHkQEWgWF4SjRZ8LrsJd8qPvN8FEGZLXjG/YDQ+dm3crkm+ruzqEBW6LiWUsXEtfOEvr4YonWyr7c+84yv5ipvOMo/IXTFnnEaztkxgnJpF4Q8s3uSgmSzadlPqlQn7t8eJh9eKQ2RNOG7EngBH+xqqEBce/CpWzcVxUTo34BgTTR1+1XZMb5Mj6kmsDAMGVtteJOiFuok1sUBqSe12oXEXwBXoquxHmKZvjGkmvssJDENc8HgI0WjREkH9nZLtWl9AgpisVsD/LiG6bDIT7QpWNtbtT//TW+8qbQKj4v2zwbUIaEgwTMCIAoVFtOxEJbQEARqMAACz/05dqdZQu1ho1EqcWK1bex7Wj5II1Lha7uXBr8VIdu55ZoKquxb1dMAskH+DAASjcCKDDmFKgq7aweMFKHzOmYo7EIAF3rBMbAWuG1CdQBclzdwbezWYTcBqRjkKk/NDKX8cMV/WoOiu9h9p+WXhrjNaG1JOXjO4BOBNiKPf0pg4xQbU0P2DrSLRrDhiCXnpBM0vtl10O3J679VZQUjMnmpOLWZNpTd8ezcBNU3ezsQBzCVemHURNMAsmZtxVad1NkqWt6sdANriro/c6AFXfKH5t3P/r337mJ6k5Qyz2PT/ORo1L26q5640bIzfZj5a4YJhkKOxcRw8g3V0QDzLoEDCZqwn1LJkSx9lTvExlwJiM4KGF9RDw5Lq53sjx8DiMpokDnusXrLL4Axiuyg6g8Mg7fTQbBB2KVTURZgbcLMWGZEn1JyJ2XwhTQJ+09niu8V7LH1yUF+6H5/YvBO3ivWTq9Y7IcKkWoyYMgt2howzmS9+m3aMjeK6ndrXXqWW2bJNxJxIqDH7n6Ar5FvAdfbPLJO/IsWe6zbs461d9Gord1rlORxFb6mFrMtfhgSs1uh8AAIApYC4I6DxrHwDAzAsIkvx1S5WtuV66zgZxRoEg6rtUk3pin07HnMvwQU/XKMC1i0Z1ZxgU4RbenEcASZINdR7FIwS2HYI+tzX6UUMbZH1UfRheequ3aaDmLMmB+vnxqMf1aG4mwI4/IQZKykQUKBOAc7NpCulGnWQy5CdIvFRy6nk9xOGwB0exgPi1qqLEz2sxUeqCdj33SgHY0IQvp+rjmLAc1BIS56B7EuScRi95JvYygMEMi8taFzC8hWjLD9ZdUS3ZhHE3+8NMlOY/+M8+FtDDpEcaNQCBRNQ13geGveqX0e5VDLsq+ikRH2rwy/RmX5AufaW2pQ9NnLl8UbviDNir9nIStDSzx5dkhFLujHRiCY0gw6ccJKUeOOLAOtqvMiv6iUczxzyhs+BxsYT2gsjieLA0aCWAYXefIRyoM6ongCgcodlLjwESks1aW0yrn5b2qb1RfeU+v2YEKUjKA3Gy+PCHBeYCH4wygosy66BsgxvaMaeEpw9R2udhKUXTKRx85xGMyUS5JAqF9GoRep17zOxdirGhHvQe1w8dztAuDoaqEUrKLqCUxd+HGDIRP0gE2NagSZc5uWBeJEgWOeVBAn19eCDaeYwYJubLks9TfZbMHZsPpkJHapmX70P08PAdPcQNNuTIBREuq6kob0OM9jcWHT2n34iSzk2WGgMv4J/lFymwh7tAEnwBbDTCKsM2pY0YpTZv+5oX1X05J9dKVODItT7xZQu2n3teGPtcbMP5XRIFH1r/KU0Fi23qbZA4wuQ4Drk73B9U+b/B+y/OAZBpN6at5TdH1BmgheH7WO4XThe5FHJAS83QOKpg4Sj3/vaYNIZFgusUggRzps1NyntaElzg/jY=
*/