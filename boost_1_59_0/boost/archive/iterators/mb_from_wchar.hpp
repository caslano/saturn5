#ifndef BOOST_ARCHIVE_ITERATORS_MB_FROM_WCHAR_HPP
#define BOOST_ARCHIVE_ITERATORS_MB_FROM_WCHAR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// mb_from_wchar.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <cstddef> // size_t
#ifndef BOOST_NO_CWCHAR
#include <cwchar> //  mbstate_t
#endif
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::mbstate_t;
} // namespace std
#endif

#include <boost/archive/detail/utf8_codecvt_facet.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate wide strings and to char
// strings of the currently selected locale
template<class Base>    // the input iterator
class mb_from_wchar
    : public boost::iterator_adaptor<
        mb_from_wchar<Base>,
        Base,
        wchar_t,
        single_pass_traversal_tag,
        char
    >
{
    friend class boost::iterator_core_access;

    typedef typename boost::iterator_adaptor<
        mb_from_wchar<Base>,
        Base,
        wchar_t,
        single_pass_traversal_tag,
        char
    > super_t;

    typedef mb_from_wchar<Base> this_t;

    char dereference_impl() {
        if(! m_full){
            fill();
            m_full = true;
        }
        return m_buffer[m_bnext];
    }

    char dereference() const {
        return (const_cast<this_t *>(this))->dereference_impl();
    }
    // test for iterator equality
    bool equal(const mb_from_wchar<Base> & rhs) const {
        // once the value is filled, the base_reference has been incremented
        // so don't permit comparison anymore.
        return
            0 == m_bend
            && 0 == m_bnext
            && this->base_reference() == rhs.base_reference()
        ;
    }

    void fill(){
        wchar_t value = * this->base_reference();
        const wchar_t *wend;
        char *bend;
        BOOST_VERIFY(
            m_codecvt_facet.out(
                m_mbs,
                & value, & value + 1, wend,
                m_buffer, m_buffer + sizeof(m_buffer), bend
            )
            ==
            std::codecvt_base::ok
        );
        m_bnext = 0;
        m_bend = bend - m_buffer;
    }

    void increment(){
        if(++m_bnext < m_bend)
            return;
        m_bend =
        m_bnext = 0;
        ++(this->base_reference());
        m_full = false;
    }

    boost::archive::detail::utf8_codecvt_facet m_codecvt_facet;
    std::mbstate_t m_mbs;
    // buffer to handle pending characters
    char m_buffer[9 /* MB_CUR_MAX */];
    std::size_t m_bend;
    std::size_t m_bnext;
    bool m_full;

public:
    // make composible buy using templated constructor
    template<class T>
    mb_from_wchar(T start) :
        super_t(Base(static_cast< T >(start))),
        m_mbs(std::mbstate_t()),
        m_bend(0),
        m_bnext(0),
        m_full(false)
    {}
    // intel 7.1 doesn't like default copy constructor
    mb_from_wchar(const mb_from_wchar & rhs) :
        super_t(rhs.base_reference()),
        m_bend(rhs.m_bend),
        m_bnext(rhs.m_bnext),
        m_full(rhs.m_full)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_MB_FROM_WCHAR_HPP

/* mb_from_wchar.hpp
gzoT6YEvsSlmgslqDOXG0oNzHQVqAqgMaRTiuaEgbcv+g6uZoqJDU2fYlhXNok77tEMGlM2TEOJG+RqJV6MDWf0HkctFbGATxmbMngNJ717AiOD1Yhf0nd9+W1Tiw1olEIzfnTsRJArsFPDJX9YSBI3+bbJMCs/g24ZJsYR2rUB7yY4u4zwtAyY2PddUwOz25+5ascwF0sW1ubQHRKThkCC+El10vgK+bVk7VymbsGTg+4wJ8qDyWQmEToe/6azMlxtsBplA2Z7n0wcFo7MnOTYz8ntLHMog7qwOxqxH0vEHPPpBMvA9t0EHdBNHBOcYeGoNE65qUHcJcB97m6p0XCeTrZZjOmrhEier5mVhSsF1Fr5ERfTDgI6NlO6C/Tw9B5NU6j5mkAYNiccmDJWZwB0+eqw3qW4hgiCQcTvQ2hM48MsyDcnWt/ShuyZZcYPXcARDn4ZWpqcQpLtqTMxnAicQK+0V0iggXMDa8+WA9//GcyDLEaUB55JRW1+UaUh7tg4KElu0UsNsP1UlefmiwmR3HMtUi16SSAEzKJ9w35RO5vf9QVZz1Gyi4mID2+VwT6buNS6aObs/Y3NiU51I9yQU5UruBoTgc2IPjA00c8E5Nx+OfvTL39GA3W2rPJmF/4DCBpxQPXyN1jpl8kCATTHWMrJAFZZqjP7zjOgXk6eZdGqcYlILnBv/d5WO3+OIScXivOQdaxJfIorbLdfVbiKOrUyZJxvA2RnDITpuEbEaUtKhR0zZz12OUtHdayV/21ojlseUN+2A2bFXikcaBKNCkXLyJu/1CG11FBgUVgnMYiT0tg1Z8kT2FOukTxvyjG9zYsCjEDJMEZ9wgSyRE/TwpZGojoDwvg0RL371j+HZU0VAuDJYD5SFox/70LLVGq5kMfrBSM1BAyKC9gbDTvHj00yzrERa0nDTAC+ysIyDbUcnmkMwsWoWNGQOSEdju2XrdLwGL/MpcFZhFIHEgLpd6IyaOsNw5XHmdU8EgBExFwrjVtwX9lWnH9NiocpNGoj8pWnfVa8/nzh6NmgGAk3rvJ9wOJVYRfi0MG4AlzgYHuEfAYVF399D69UYuD0PYjIg62ZWDUs+XJZknjBEobjNhCZakWwv4iIrJvx1zsWwuM4doB7pLbHbwHrUShfTkJCJFzeVChFQlj4V3vwBftGDUobSDJUCIVZsHK+4v/5w+NVjmaUtsT4QiENogeC3/B1dY6KHfymgIcM3wubfPZ8SwTATjh6V7cs8SLNrDuO7cTi4i4nCDME4Mg3O31stnq5BjpRelMl3+EBEU+o3zX3eFba1y66JK4BrtvBJOuAE5zXGa40L5UlJe9qFS8cshKCjnVWl0ySZuXJepiKuiUHHoVOLI1D32O6UFkP+Cjg+oGX0QdKfX1bJzhJHAiuZRVBA4E1TiMF6fW2gS8nTg68a2aGxY4ZA74D6vwWBl3CM6lStPMZ3fhPknOIZoUN+uy8BHZHf73z+gZNIFxheI1EWpzTlLV9gYjiibdXt6Kg5KaBThLAvOxJeADODXd4mlx1zVaMvIExNduGNtDK+P8ClddRpfSzhCqfhZx3yNAvAuM8DeesLPSdUrimAW5zs7KlXr3KYbL/YJJUuDSFUDb+EaPI3UEAQl0PFYHM12jMp1uYlgCcpLI4LFLVmazeucRtFa8jRhM0xi8YBBYuBd2Fz4tFT3zKbBLv6ObN+dlpMW7JXBIdXYSyOJV59Snjy9+rnVSRJoL9ALfIvcmP0xzgoVyjGIZI8uTc7x0dThqOFTOYfLUXBeZp1LQWcAbH6M46x6I/EneS2pVdX7+9Sp43yeZ142OZ4fByP+Ph3FhDVt9uTMHw61Vm4rMFFDQ45hSXqdH4/KLty7ETk83sgKUT6bBntnbsLGY6QR+ygSQURslJT86GABpsITyO17fNzwYEc3NDqgQepCElXGU5lZwFmPtq+0hpOKlUY+1/HAmGGAd6QF86wE1ixJ1vUsH0tFpOqYlWVMckbqMusvd65i/KiP7/CcT0kgjYEG3GBIud5KXxcpQkZNRSK1z3cCBeX0F6ayE3PEvpQGB/bjLN/XI6157jzDTblw5orU7HUKOAni2VzdHyWe+++wP0/Wu+nj088s850HlXN9DUutmM4Ko/9WU3toQ/swvgft0nWzTJA1TQD73nT2JhyCJfFHso6wSSOwFeSoCB9Y0RQ1IrsU5KuI0q78CqR7wPyHwTvkwjcZgxiUpiAeB15RIi7QZbiUKxdDBciV0PHqMzS7LH8F8q3EcRA2dYgLjnF5qz4plh9fvLjvxJoRnm14AkaYpvjVPq2vYQT2xlFkySkXDlnyUQnVD9XvA4PD38oGCaeJHE1dgUg8rLTFYZlV8Wo2YRMuP1eEahV90jD8mB52EMMC9WfHRjNkwgZPcUkfeoMk+buvSXrYMiF/krbmnDNXKvh4B8ZiohX3fIH8+pjHaKGxjmNEA2BGNk5+MRSO/Gw1pbUrGbQxTKKzG3CWHrQyCYPmEjKjDObMRzMYowMhugfPvlj12yxcgz6PFw+1Y4ouop0VBIGW+hG+XLlx9NdxvOaJ4pRYd97cPAyDIrBo6KY8EU6ti/Akl3c1+jh8cJIvCX77KnrS5ELg/240/kg/cXguoYQL+P3pBibt+w/g86+iZLRigkkMT0kdiC7dC9txqbfc+9OJGv3QuRe9tZnTl7YhvG0XmjBrWN+gEMe3WNGLFAMewzvna0a3zeWnX0y56tSVUKBHUMdr5ZEJ6ILCTe7Fq509UqH6SNWkWP06EynD1w0qnYKN0YDP2W/Hc7Oc0v2Mc/yExicfdTx+JCTyyIM0ALLGLCRpHILrKSCqKJmSVcUQIzRGu4X4sf5E3mPPkSrOQCD53SWbOnLz6ph9voXpbcwPG9NnK6OD00kDe9zlxhHkYiJmAo3A1QWTixN5oYj90uGaL7aRwrVu27UCIu1zRUM9XrbsTtyc9/BHeqMgDCgqh4GOXY8zTOTow7QgwoTI1zwAPaf/36gjzr+NjUEVilwGnOJvalBXhozIl1/S5ddGyI9XVN6I4ZYY6vfYnV0qWMNzT+093atI/xvEkvgvD3OyjnxuLqF/f5FJdJ2KODhIJVYcmitnppBiLhWdq4bujXf/bdocuwL2N2ILiV/s+zZsxCusi6rVYmdL/CxEpw9pf37t7gqb7QySBlZsrEYsd1sxCQnbYbIVg+iybZNyIDlGjrOEoh+WIfvgLRjWbQA7EgXt1Jtf1VkA61v8E+vYZTwqcB38oeAkhngW8hRxkAYqtGAg2gTMh+cZQOTwoRR7MZOoC37/L2OPDCsvY1tmHLpQzjI5JSt7GzDNDD3LuWA1yv9cOUl08dAL/2uOjH63D0MOhdBWgUobDXpvJHLg6fANOyOGsWzf5fA8i21EYcBfIdrUqPB6wGQFAs+BX6Zik1urh3oRuXGoDMPd3U0lDTH3NhRm6LS5mT9ufLOeg5jspbmY6lfqCNb9Wfm/mVQJZ2JOPRambA5dTjwtqkDci7FTTZC0J+onCTHhzU+I3EOPGhR4rQesviNeAr3JqqA3bfeqKZXlG9wW6lQHndiHbMHB3ATj9lUGEbJJ93BICD6bV8hf5AkP7DGGQxgB74/s6Jxi+gxXjCJgaE7SSlk8csaO5g26/O+skLhSdNdQJ/RAwHcZa96LsefSRP80+xTV3WOEowULKWaqih+YgLHleOc8Yc1/MQqUTGcy2nGQivTHprQmMyo3QxCqIwZ9tOgF/NHfmq+NEk6atUO1MnIJy5gnGQ3pOXHhP+CI1nmwPaLPRIvlCWTjZ8YxpPiRkIbr7XGjVUThT4rM5iEzCgshGujti8MUfGa8w+pfOgiCLY6e8cLBPlV5aoXNdqRY772s1ZPogoJBSMYMRgyv6McmPsVGGzih55pzfkCh+6DhOzDQ2LLRFGLX6//g78H6tonpGLplCVw4YH0DPwUwlCwx2WdRdqG9N9xKkXO5hTPEMuzo90hwDG8nMkF7rj2bswSP8gdsawyYVLIoILVhiWhuQMTYOQhmlPP3ljH78Xg8Q5LZSXxmyHYTOirPb8WU9xADApqULvIjmLATPqS7lMaR8cfppYF3ux1Pxc17DN90x3xxwriDzzUHTCIpT7DJhcNP+IeDFcPfVx+lYfS73RqEEw7mDfsuHusJJuvEyocRWetJPJSPBQ/PKL1CQrLmwD1OgBWygSmD8z5OIFbNVRetWJyNyN2IMXSDeQ3b1PomU7umMqFA1sUVOYVqjd/NSPiiS+vmueo/qZ9xJQErvzOUd9/IFfPNODbK7GoCGl/UK+IoCm8wPjjOFsMwU396oHISMnEAgCi5aSnu4dbRqvN5Z67R2usAhCHvPWwgWXQO1PEXyGsZjpIVMwz4wFNns2WY+DbfpIShXRXJQ+UJNabLRgDAU7o0fJKSixhxEJ5W6s6gVAfyR91R+U5hUBb/HrWYnWHQghSQ3m743xQaGN+XXR60SHCk4X3YgCEsPnIEoDdkoljntE2SKAGJKvwj0vDgZsDjkVrsFLcC3xOpBkBg+hUxfBlKxL8VX63xeQIwbELIigBbTgz8VkDW4nIhDbwCIBn8I5H5YC9zDXUzqILvNO3O8l4YVtBumC+Q+2hxW35SYMncxcWyy7TNLQLnQeFhGfNVJJzfiQVsNu1LcGrurPIXDmllJ3Awr+CWlvJPXdJBVbwBWCRKtbJJWQ0S+0FJI1cnZEyBcBLl4csVDWdV8sZ6RmCELzOKxZwYTMpm3k7H2GbSQMmkrBOlwPhWihkte8zuJMUAYGnDFtfH7NYmDY83ivIh9f1tOECW6FzQeBn92teuzQytCyZbUz68v0+nziL3LvzwGag7lqG0oVW9S+g4KQyI2oAfPddxk1cqqnc/lBYH7G5oDJ89sZ5cuEDBPjr+iJTkt67ePE5P9P8GTATlDZO2dQSX4yYgh1b9HD5PqrkKbSUrzocChVUMWu/Ecz6tEUsPpJZ9J0QLnI4sCGhwQSWZ8E1BJbmP6fAChwBfiH3Yv4fB5CzcCwIsgUDDNAAx4SPN2npdLLUNX9+8fRKIauWp9M4fRd9SXvPKNU0i+8E+2vmNVbcBy+NjvAGC6ImOxTSpvSCJZwCkbjuTtL7Rml+wkHLAe/HTTyI+79WArEhjcIjZVGLqe521DEZHYPRfUSO86TMEUSCZ9t3myxz9b549KwKgPYTbdyBc+a6lLQ5jIQH0oUaqXXWLOUMEBB7QH3tC1cjJRaCVPH6BlhczWii3dI/3zqM+UFBB3a17pJHJcr6iifDFEkVKnphjFujH6IP2eNlt9x9TS44PS5HNU4K4JjMdLx2ElWvUGNQ5iIdoJLZJqNX0dBxZkMwruBLYzeEeDELocmRydLKNcDST/rx773xzBrI5xtvREJFm5E2ubeEIL60nI/8NpjmvvljFmUPkAOOHmP7lLn2zfky4vMB331yq3+nuryBMosSERW5/lLc8/hIE6+ldcVg0sxDzzt07RHtKQyocBGP1RGKVRRT6SBJNV67C0gqNRr7SeR6Mp8Wxk/zhorlq1XJyPCWkEjRM/pTYevFRp8wPH08vuiYrcGj1TbmA6PCJU8/x/WKg/uJ2YLJviPi9quFujdEsb2bCdlZBjopAKFstnYXce45PwXw8LXkufMcvPQt3wRTYWbTYOPMiqX59xxQl0F5XP0J/mxZQvVgTIeTV/Sz1KwMQ5oxnLapk98rGFBsBHKo4pz1A7q0MEptdXM7jkStlju8EFgVhqQCokjuKxPOPSrN4Gh4WCxe1+JtnwxpfTxLQ6+CpnyMNgJMiJB8AvnbZll2Xk/5seV9anK8URuvrz45g9ImDzg8tE5XBC7hXdtt0NYY3dCIV6CS/q65T0F4rdOqs3tuv0r4WrJQieSZbi0RlhyQbPGeei12NwBVex/ACVxcP3a/sUd8OZxOHITjSFHgDkGRxUNuAM9A0P1P6CvC3+L0H/0llA1okenPLb9zPQonzXVNTWGXegs5IQgg4qirm1tvNwKEeXUVEtk43kTCxot1wYMA+ycGnsZjrhhirwZQAQZz3zxbMmZmHzKcfDWVfflawpG72bW6xooXaMvVWt8+z/CaZ3gYim3YiwFjqv/GBdPW4IGltPXxaeJ7BMBjJFKx66J7IofKOvFU/1LuFjJRgk7veVCgY64KG3XWOjpcPXpRDBJHHRgYaEmYt84zDF6kSNCtl7tUz3CFmTUJUWP2DoR8/voc7p8Dh7CwOidLeAnP9AQiY+GaBWHhcpAHdLn+pWz0XEZkxmkizhI78B4hkZWTcqDSQ/RXL/WDakkPEs3aLfYb94NZLpaeJSljKFTXXMFIBSH/k7pG201XQORVhz9aH+gRPJYdLxVBJsHPwM4Ijw6XoS8825dmqXmmd3qtxCwsT7JOKLbKW6DYekUZJrHM8uiEZOhdcayUM3LDtFbSadlYheerFum9OAIE3VGA/wIFRBGUcU6ULuNH0kkZvv8AbsUdj1QbaOTKV9gIm5kbjh5yY+wWxC07BTvbvuEF58vxZpq9MwPQBhFmR43RcMsqt0IHgDHrwxdMHaWHWZze4WKWy6MRD5t3gYqodh7QQieC6oqzkrA3IJp5Dbu1BYF33KWct7O0cZuTrBr75YPy3FqahLJNf49uho2xIzLxXJQcr8B8rkhj9olKnQ35TsTwhikzb0kClGH4SbaWMk8uwYIZDZsh1SXDVzNJmBNAepik0FzwHMNT38/qJRucbTXufIy6hvXn+vPjYmJwS8HdO3jdz5TCV1XjKSSrLPDcSlDYx16ZHMfc2WpCck9qAOC3qAU4DVqNk11FdfoHy5JHEu81XvLBQzEVi8RkkJxVLSRR7kxuSOjUZmDpNoBwSI4hIcacXOWSKTPeTcz02+DZdstEm0vndWeYXV818JW8WWivmqrPFv5jNDWrTM9UPSF53kqt4pxxTvaYMiK2bhkc1uK5LZ01LjZZx3+0oJPS3V+8NzC8kqM4cBVJjaYnTaYFyDggkz9us7A8XQhRiULGW2vzf1WFbWtrj7p1XqVZB54acilCxihZWp5fdrcRERYhCQV1afUwFa8s91U0nzv1VBHC9WcdYpf3/qMHkl9pQQVRR6ObNQ1fpd/EyBAWy19VprhCADNMvYPDoMRJxQUlx0T7MmcHl5IOLWmnnJW0cXI332/WIUGeRRO1zAgG7A6obs5MU6Gz3SHhrBaUKrSQ/3GaHbqV3oB7FY3QinJbpxgvV7I8XogjQzHyt2qTp8nU1dVVOp+6LABOxCcJAhICoWBgeCmUEVKA1q27e92AUeytkOgyjAg7fioJNmbmMj7vuIlP/YVQcFaw+2DLBYAYmpg7WxUHT1xoC4saqAjSKKwH1aWcX/pR/UBcG6+KKaw0p0ldVHK/xIu47lvIee2AcaDerUlsqSX1nAIGiVOFe27hslJ01MGs7DpfLAaYNiCssFYkOzZdv9NSxL//z+jeEKAqnEBrTrKvhNX/ABuA5H8DT57XRGX+3TM29V0TbeCGgaQaoIdS4KTpGdG2u3Sia43RZDDOmurhcyr5LIxzBpDVw0eXYGQz8zhGM50rcrMTEJU6QHBj1e4oVEkxZMvN6fqVB8faRxR06Kn707pHJ+qSRYVl3qYbO/QOLf/vLAD6REIv
*/