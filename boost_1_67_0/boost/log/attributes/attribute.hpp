/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains attribute interface definition.
 */

#ifndef BOOST_LOG_ATTRIBUTES_ATTRIBUTE_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_ATTRIBUTE_HPP_INCLUDED_

#include <new>
#include <boost/move/core.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

#ifndef BOOST_LOG_DOXYGEN_PASS

class attribute_value;

namespace aux {

//! Reference proxy object to implement \c operator[]
class attribute_set_reference_proxy;

} // namespace aux

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief A base class for an attribute value factory
 *
 * Every attribute is represented with a factory that is basically an attribute value generator.
 * The sole purpose of an attribute is to return an actual value when requested. A simplest attribute
 * can always return the same value that it stores internally, but more complex ones can
 * perform a considerable amount of work to return a value, and the returned values may differ
 * each time requested.
 *
 * A word about thread safety. An attribute should be prepared to be requested a value from
 * multiple threads concurrently.
 */
class attribute
{
    BOOST_COPYABLE_AND_MOVABLE(attribute)

public:
    /*!
     * \brief A base class for an attribute value factory
     *
     * All attributes must derive their implementation from this class.
     */
    struct BOOST_LOG_NO_VTABLE BOOST_SYMBOL_VISIBLE impl :
        public boost::intrusive_ref_counter< impl >
    {
        /*!
         * \brief Virtual destructor
         */
        virtual ~impl() {}

        /*!
         * \return The actual attribute value. It shall not return empty values (exceptions
         *         shall be used to indicate errors).
         */
        virtual attribute_value get_value() = 0;

        BOOST_LOG_API static void* operator new (std::size_t size);
        BOOST_LOG_API static void operator delete (void* p, std::size_t size) BOOST_NOEXCEPT;
    };

private:
    //! Pointer to the attribute factory implementation
    intrusive_ptr< impl > m_pImpl;

public:
    /*!
     * Default constructor. Creates an empty attribute value factory, which is not usable until
     * \c set_impl is called.
     */
    BOOST_DEFAULTED_FUNCTION(attribute(), {})

    /*!
     * Copy constructor
     */
    attribute(attribute const& that) BOOST_NOEXCEPT : m_pImpl(that.m_pImpl) {}

    /*!
     * Move constructor
     */
    attribute(BOOST_RV_REF(attribute) that) BOOST_NOEXCEPT { m_pImpl.swap(that.m_pImpl); }

    /*!
     * Initializing constructor
     *
     * \param p Pointer to the implementation. Must not be \c NULL.
     */
    explicit attribute(intrusive_ptr< impl > p) BOOST_NOEXCEPT { m_pImpl.swap(p); }

    /*!
     * Copy assignment
     */
    attribute& operator= (BOOST_COPY_ASSIGN_REF(attribute) that) BOOST_NOEXCEPT
    {
        m_pImpl = that.m_pImpl;
        return *this;
    }

    /*!
     * Move assignment
     */
    attribute& operator= (BOOST_RV_REF(attribute) that) BOOST_NOEXCEPT
    {
        m_pImpl.swap(that.m_pImpl);
        return *this;
    }

#ifndef BOOST_LOG_DOXYGEN_PASS
    attribute& operator= (aux::attribute_set_reference_proxy const& that) BOOST_NOEXCEPT;
#endif

    /*!
     * Verifies that the factory is not in empty state
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * Verifies that the factory is in empty state
     */
    bool operator! () const BOOST_NOEXCEPT { return !m_pImpl; }

    /*!
     * \return The actual attribute value. It shall not return empty values (exceptions
     *         shall be used to indicate errors).
     */
    attribute_value get_value() const;

    /*!
     * The method swaps two factories (i.e. their implementations).
     */
    void swap(attribute& that) BOOST_NOEXCEPT { m_pImpl.swap(that.m_pImpl); }

protected:
    /*!
     * \returns The pointer to the implementation
     */
    impl* get_impl() const BOOST_NOEXCEPT { return m_pImpl.get(); }
    /*!
     * Sets the pointer to the factory implementation.
     *
     * \param p Pointer to the implementation. Must not be \c NULL.
     */
    void set_impl(intrusive_ptr< impl > p) BOOST_NOEXCEPT { m_pImpl.swap(p); }

    template< typename T >
    friend T attribute_cast(attribute const&);
};

/*!
 * The function swaps two attribute value factories
 */
inline void swap(attribute& left, attribute& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_ATTRIBUTES_ATTRIBUTE_VALUE_HPP_INCLUDED_)
#include <boost/log/detail/attribute_get_value_impl.hpp>
#endif

#endif // BOOST_LOG_ATTRIBUTES_ATTRIBUTE_HPP_INCLUDED_

/* attribute.hpp
eHT2DlQW9ED7iUjQRxqE4yBOmi12M5y27fgg+hIAJ3tIPbh3P7aHFN2XTcoCW6eeLhF7QSUsqtwqUIU/45uRyPsn7JXqksrRr9u9Z4K64K8ZH3X8gMePeDptw+uH4nd365cYhq6N4anRrhMASk7RAUCsSPTGsyGNUH5SDCZTMqkxyBjhNjRNDHuPslrd4/GwY0bdQ7feNuASn8KdJ+GJmFQ09WQ8+z/RL+1/RJOY9/LSgWjBgLZ6Heb8LuK6ECxhAWmkarXLny3C9WAY4UZoZkSEbciP0X/ve7piAxTdmepGGb7bXRVDJDj4vgxGIoY+WzpQSwZTWGD3iBjCRaKmUexCCN9Za3gxS86ZRpC1FWipfmPyj5DW2j7iSNtTkc6ODGT9AkIBe9C1iYLfLy1+deYR7YFhOmToNscz2Hig8DCTTKqUEgHweiKohXuoN9ywe4LuhsUWEhIZUsK8Jhecw2hnPBbkfcbh4bJ8zd6hOOB4+kixpc2jB4flin4wNBxCVixZl/94seDbVQis0Jf6odd65E1eseXUsXFP0XUcuQeMPe1Iy3R9Tka1NRlxGPY5c6nwxAHiW/efaeG6cwKA7OKn6gNDX2f2p5UIkW/oiKtSWGhmXjYcwVx7pYuoPcqrjjmc9UHVRXLL7pCcMcsbArKzO7kB7GW9rmwS/v1DmfOWqk0B7tFrCWwIAduUEIOtAJctrrXTn6jhgvq2vAoCXxDpB0dUWBqoKZYTGOLde1hiQZuQj8cGMqeXBWPxVSY8SJr1uhmnBOvYNqCwr5fNaLLv+fu4hBwMsvsyDRQHBRqjEjCafeX142vmh+kmuraaeR9otKQXK3IrhTZXm50+HVhsaX3lmVmZxb4tLNUZMq1O23ENsrHW5X2LqxL4Itvyr9H5aOn+3sIYtJEq8j0aHLqizebUho78lWDkccV+owbNKIMzPrGw0oWzbAfF55QKlX5FYxuYf1CcU3zueZQkPAYf8SIe3uhcifqt1qYvlsKlJ61OSJcq3EOf37dt5u63treRDZ2749tfo3ICbwGNYIC2gt+Yfa5ias275IK6ozHlCbkWi/NelumpcZ1n2/gGpLiKhGctZqgKa5qLRcorPkb3PZ6Djf3OZ+1qZq1QIBXcZhreEv+E/zMs92bdA4gCwM0XFR7TW11pCiWmQN5pWRzmAQG07+QBaGOhzezoAfN5nQXnt8XRrH+cfX1mwHMir0ItmjFxr90qSiABUpRqNIbm2VdO9yBcXoohBWqWyqJuy7crTlyLd6u1hxBdZ/wjcQEHBe05YwMDd5Hl3JRFq176xLye+T1IuXZfylNDs9ATPiQJPQ5K65vJrHKrfu1xY4KE4EvO1e5ylWztQiTsiqJfZ+luzXSD24POoxSDlogUTUFVgfABFzLtYEVAv2ik9LaClx3YCTAMDgEJ+ye+WLiY1iKtg8oSL6at/3xOebTg7YvJzQh31oaxxol6+QoLBqojHNFTqdPoacGzzaz7tFX9YRbR9AukBLjv6xz8WrzJIF8CnWSHFi0dUwkjMZ9jJK25l+qaF6H0KPqkyw+DwWW5b4k5sFIK9Q7sVPso2os2j0Sbowywmw5gWo7r8CijAfXl8IHlmzGXuQy6Voaw4syYU/M4TCQ8+6Go2YYIZHe+y2gPQt0ZQcutIFAulKmxsfbS1iWAjEP2vnt3XDcEttWSCzhkmOv834oC+RYwcYhFONQyuI3PFADAIRvSwvv8kaIEf8jaOwmR5f5Wp5St2w7Nb9FOUl+BxMlx9L/UQYSHkn5benKNh4+Ll1fm1JO8TZQgxzuBzdCwg3VDs4Neo/EdlMAcjz1DX+1K0rh7gqNDgZBAHVWtlZqGKrARBC/0SkLyyagSfqN3+53JJoStmrCFrpiJZvRyXxL9oaKWIQEtcy4Y/6Q/UWMgA2Ob2LFlIh2B4qiAG+ydFKVbsbUmXGFRV1+ih9xxSKQya7jNgDWDJFQ+Z7iuxYdQR2wktj5etKW0arufFeK0n4KewAyWjqSEmyQC4TacUpd/RcCJ1+dz2HyCNXYtyd/vlFljs2VKiiGmL4bAXnqQkS1Q4SHJhu1tZmtw/Nfrjs8zlF/LIpnyKL+PwXZN6G3OAuLWi2+MUvSu9Cj2z5qF9xTDqosTeHKqekdAYsdn+i0z/pWPZLFhX3VYwjJ94uXccuUbjGGFzstfOSNwHzxls6feIkWtgTIEkRU2mAsxOkIgb0P9VuHClAdGJrfD+NdwBDVmWmwTqjWaj40TYd89j9g4ZvwXPhmlKLNy+CObSqRYzcdSfEy+sy8bSFg2Fs5FwtBFF9sMOC/uNRHQ445GLfRAKl+ugJpccUiZ1N1/H8L6anzJH6s63Rokagn7Zwyjhp2W39wlmMp+sQUcuJQdB08/IHU7dWyMJFICMH8bb12UsHyWG3JpCoKuvC7I5k6h6qGlkb21GOySi9u5wpJAR3uFOC6EJCaBYMY56bz6zG1sHrtEcpOgCj52q5EVU7QGoxF0BuARQpRDVjtktiC1KWH8OjM/a+AGanjrABjx/LEWS5NE3DuPX+FcOTcE9Ke+VpoY7XemKUld8tijFo5L4UgSSU1nRO4ItoJDirYLLhgsyTc5KdNoy1Kmh/gxoaQoqm8xLCe3CJgRFwdri11SgRnrupo/h+HnsnFsQtq8WZax4xa5QCwmmJQQOq2IBHvIqFVc0MdU0iZV8peBg1y6oP1F3/QkNNhE2tiAr/qPbhKQB6eD5JzCRfcHf9QHHer7K02PbfEfHRCHcZinJxQzFSeK/4/qGQbzOVsS4CoSMB4uEr04Rt16znvDTslyAdkIkdR0lcRTlSUJWvt+T8RDFVYWnCdjrfEaCDDl0bkTaYhjyFW4rL66iTOb83qDJEn7YlmttG3svJntYpZ/shi7pzK6Wk4h12Uqj6cGkkB0iVmwCGKa2K0gdGRoi+WdI7tHNwqXPVAqCl+1S7bdZtv59G9a0H3ibqNysGO3M5OlPodoGlLeAeTFaLQaPSXG++G8QT987/NwHSMm/W0NlP+2y92U4Uc5F60ftrxC85ulDmO+GAxZcztZ2N7YDlfMnFknXMPDHjpry/1pFCqNAfdeFiH43J7rn2ZX+bt8/ieEdHMZ36yGfmTzW0NFppOtCg7xKVRNORiWdajEz5LZJ7vFsJkKaJn8i3sqKWzuAD+ZLTqxO6I/10Kue5SYl5fXGT4Qk8cG16FbGYw5uY994o5qCQBvwnKO819Cazn2t1XqjU2sSYqXKXrDTXTQ83JIokDxMXYY5Q3azUctqFWOUqTUsGxsPklGEe89KwACLs3iwF6XnAvl07ZR5cUOw6Xb7F3gRADD7DqN8y7lRxAgqYRT7NlLkyxO5QdPtXJoK1z8aN9wEmwee+q5qB681leOz+QS+9cHPSu5ZlL+/nxg1sPe9v37P7COQ2mWUwqT1vHBQ9aTdMSaEXamQEhdWB02hgBerFKJ3GuLQxbA4hogg+6LM+UaUBNltpKp7xL781xGo5TQKGeFCe4hLzO5Vhrk2wo5kSBmwBaY1p59ijn0zvIoEMiTzgz2cktMmx52DhP+T6ZmBB5YHpEtQtDrc+tK5EyOf2n5jmY1HHtE3qbB/6klyO/IXsbJJblk3ot4es4nFL2YRrLurR2ngx5p4fcOQbNAKjEaNh/1yWdf06t78xQiJoY9p+QwZVKfto44i3Deq83zEcZGPiDJWtgmzvhaGSY+DZ0FEdTHH5J+Cf43tUElVFDqPK7IvVlF9J1yRbSmcySP42mR7hxC7U9l/WY1FzLYVQu9ZT0iwPvmIF/Ett80FWaqXXdY3ysXjUOZh4UlRVjumwwT5AtGVanNvfSRYkOjsDC7akGrvIvk28I/nYYNW18Up8sU5M8a045sENCXgulr5JaJjT6vTcanr7hIe2wm7Rv+ixdySRCw+Q+iSYXd31H43KEYduv2bZYc6KhdoK7saJCl20IbhhemuBGSPDozVND2up3n+P+xxq3ETPAVamtpTAEwVd85UF3zJYxCZCNA3k23QBcj4qqXG6Hgk3jmuC1BaKCJ+vqa7SkSa5BBjD/enUbhDahIZ4vU26fmqlqHCGzIrbuH3v/4OQ196mCetfmp4/Prb4bQr+Nj/Uxc4Ber/hCL+ZpNnA4IdEUNDjfbmS0LRuMU0jKR/Fq2PUrT570CFlMoZdsS8J0VU+LwC14G6sxAsm/rM3pgkVHdYcWWV4hyt+NVMOzuTGzF+Cr8ZN550g8qobvuUry9P/YBY0cMqn/GJLlcKs2OFqotpeOMXymiA/QPFM+rqr0Zpqm9suu0uusZxGjecATGnl4UgGk+osAzv52OwwoG7NsFS+mj2KMqpOco2wI5rXvyZRTSWGSs+U5IvG5zKTtgc4nNA9CkQ+AvNxIZctRrP+tkChGtPkpDP8CpTB1hiB4r2pdF/bk74J6AV6XO7QamkwZa9a21thvxwLcEJhmtFlL4lCgGRchz5oXH+Q2Tw4Jb8uYOykZ4mYkYLZrhzjvc13x4/fXRRen0h2CtBRsKpqBZrxwP+2EVAX+DZG1RS4gvgGStynRgYtqncpqgtR2QZE5vXOdsyIY+ZnofkC/9Em+Bq9hUhoCu/pwv3oFQmQ3pQOasiI66l5FnUdT7p3qbgVlWHZM8P74Jey0zsZ/rvKiNrwrDLpnBQr/UdpbJQ60MZiZAur8snx5Su+fwkDesw7O5zC4j5WFqn4muOqftoYnjz5oKLm9bjHzINE/bo7O3amHWZ/ox24fHSPLKFMIHKahG9h962+eiogvjgrgMpBRPzXuIVmaU1ZD3jMRkPkZPM79mpQSYi3v7g9ZYZDDJ8Za92wFKJIGRKwEC/F6J7dLyy1RTaaVWdlyiNw5RRsKS6F0tQP53/5JZqtnwj/Ay2R/VltLVahdCkKnh4HSc5aKEgvWziAdYJtlJe9FG97VUC3nb95aytMXo7oxDbnbX65Jvn+2uZImjJfA4E9TUn3Bhrwmj93JZlLaQimdGBOWux7MgkERLM6tPtIZV9U34QVrUZUlmm9JdsmFvsNyr7tB2H247Q53/9kaASds5amxnGUgW//PshuayFvEADyzw07+PL/HmtaKrF14mCmUMnvVrZ6FQE3u3gD036nTNP+TBdQ6CfCzPxci3rY7CWqfDk4rQt0++NlYGZFMAT3q73dDZdEHv7vKMeIuZdOpb+jUYBVa+LBre2HPfUGHe29OyQHctUyv2Z9bAMLKEyMhU9iuQi+FY0Y3DcDfHVNB54JbcubGeqMtmuPhBDzip3OQaFg9WGVLZFkLzI7WbcX1g/o7n99zqYtOVZMzVPUjpCd6n7lUhb03RK/KWpXN+1ltqLaYp7OAu5PcvWB/me0YlA3KUQpxPAf7GsCzi9PEsR//4ua8z4BnPYpSacF95KgrCdjwbzUPxsF5syxbo0Dkp95Oao9Z1JiHYxjap4y6dhzREVItNsZYGD+2ZAx/ihlv/LHZrR9EW0giZfqi210oRLunkR8vt9rrz6CtEQdXDIY2PRu50/WFrWN+d8LNfNH0NpQSPRQ8c/nNzfwV+I15/dbuGTrcQ90hEsHTiZX1knobz7fli89n3JC8TB0dxbSgJgsnwfuJW2FIuZw96lTywIbLYR2TOVxyIbikYPZhmAzG4TmXe+dhguwZJdqOT/xSW+aSouhVYZ+jddJUP7uxYDFMQTGBKVB5yJvNqhHYMkB6Zhh2npBBWcbXPH9ISIasmH0KNmr1s1cUA4/yjbYdpbZC5QVv4QrK2Yz0VP8o4Rj/h15/k444eugWrbVjvXvzOxh5mn21g+LXGUEUJ/xBVhwhjcJ8Qe5widRJ1UWNUodCco4iICegi/oaPll279+HIWcJrb9vibeL4BHbZgvJJkjVmJMsQdsehpynj07bVkfVY08Mdqcou7uG0z7Ls+NuLjk/uyp3zJkPm534sYkM1ISOycBltqj5g0xkaEeeIHWqBu6rUwcgCdpgPJWtAvwMZ7R/bZbmyTeoSjM3yQ8dhsrLdolU/nKh7pKcyMwkPW40CVgnL33c7WYBUSYbccW1lyiO3jX/wMsGzKVzpcX1uX1kLVrxZMYLHnp4XYE1oS/KGmVXx1Tig/KJxmStRdNON+yn4cqRjb24VDQmGopUnU2GNlYeaWzQUtmdbfElC0ZX9UrG8kAarmAZFIV5wteOSrlqahA/x/3NTJjq0c+GMcvfA1rssWIRJm9r37h8xiQyDo/JaXOyA+Mhow6yNMETgXnmUdDpS/ABSNM1BkipZPr5vLwcbjCoG30RBalGTAuKxR6HPjnpAyNdqXzm8a9qW91pKCPc/CcZnwlrTi7RPP/X51tXoF/einjwhTmiMj2H2moPZ01IEBck79v6Czw9vqoUr3Fwm2fOBHSA05tVltBUd4ZAAzzs+DTQzuYzSaFZSL+CkM648skt1OxvXHaUd86XT68LnW8P0i5ZJoLgQDXBom9xUYP7u1ZCWzbtsoEPEuTI6e80Xpd3aefgTbGQ60+NydkEpzAwVT2Zh65qCIeF902Lgf8RV4Ls/h9E+Hv0Qldrb+670UMJ7b9ZZu3W9DVG7Gv+GEPURemw2J8g48xmOTLbkP9U91xPa/DWeLNbVz/xUHPwZ56yO5fgdqbOVNIiPPmQhtay3xm6cv9vx3yM9wiiPP4c+2hK3HutnoKd0AtmlrICLOqpvZJQmvTpXRYDoj4ZQt+yF3Wy0QY3H8mHXRH5+jcPTNvca3JCIfLuHOXb6PJj/F7+TBQEHzC0cW8RV2yNohaEKmCtsHILhra38qJ6xAsTSnakkevYkHuK59o1rVnHu5cHzi5DSU7hPMRJFrQhY/9/Gw/MCPQ++0s/ngMgh6BZG1DGd412I5vf1Zr19Z/c53h9EIcnj/R8Hw6vakk9LBs4C75SvZD9WuBOS8HrTBG5L7mFrFbZKwpzYAI3BlYxH/i2OR0auqn1VcbCSiuNWM+uMq6XEY+7pt77P6Jnn+Kkmlg7GnjKxCeN4yhN94mfDBVD9jeHmaUiqbjbhbKBqelroLPv75qO857aH4aFYQbBMq0/MU1X2TTwUrOwwRZroKPkaoNc7UKYTnYmxCuxtC4eRyNzUjaX77zptFujDB7yGq0nWccJ2UZgQZcPSm0W2e+Za1BT3sgGQhzmlFkVa5jPruQEy0hedy6OQMKZT5XEnmZSy5YX9aMzuiGuJz3CBBi7HLpNXuRikzGHzO7EVkogJeUtqWKDgnS60kErTGWKPSWNdWLSpXttYPYewdGT4E7Gg6t3vOyGt8ehjWS4QnAnxrn8X4F8y+n9kYh+SM0/XtB055WrWTWIjc7GzMKg7WKrV2AaQH5k4AG4Kg/aupgt5O79cW8SRidnZ1+rX+du+4QCwT1sQfNgwyI6AG9Knk5jUUj/155ltIJTzAwytbC7b29opgbYPhshREwYTFbnYKDdjG+tIx6QSJCveN9/547kwvBx4++D0HprUUySg63rxvfDyajQH9khIVfwY85ZYY4wdPbzljpEXFZa5K8+gwuBA3ObPpsFqfK1F78gKqGfVYY/M1Owa4zOTpHjLGU6kdESOOW/H7G26kVkv/94yAhWU+teXaWOrfXFJbZen3/PMJWI6J5WBBW5c6dxNxK7fmt/ZE2mH47of08xHWUPplwNnW2+LiLMyNvzS38TLsUVuaruyJgJliIYDSRkrhxcEDSNLH1fnjIzB2uuG7ppIUKl0onz5+Ip15kCGyDqu3DJCEhL0ozqLniOxuU55ZhQKexsZ8n34tNZxJ1bQaMJeU68ydgvEAJweVDKK2HGMpda9AQSr4JAwKifryopRbPmE1662RvF3NVaPfJpa6bfp4fMPvcQsKIT8HYp4z9nqVbQ+K7PtNH0MRUdPsWPWFf2WgNCI6gnS0zvXmRFkKdBzr4fj6cw2+p62EQEy0dZsB2MG5Z2A0iEN6id3mEAOHS/JEpKcy0Qoh+JiNsVx83T0eV6TFBQyOXLcvbbThSAgOHqFAPXLecKxxfiJvCgEO7IbV14S4JCAzZsDfsU0TYyFp/zZaR2d/ibz/MUEIfW98WtX4/07Z8X80YX6RzWJGkM6/vv/PMGYgfqzkxi6iq2OmCeY0T0bnySOk0Q3CYYKa9YKRKuBgdGbfo6ko0iHhD3txznxdaw84KvHO5zYPMasg/guk0qi7iLBPsftnx2OdEeNqgb/UciBWnN5aGS9k0yVBh6XV1DfGrMQrUv33tUAIcIsiQaI/G+3/aISYSgjCLszHi9i74suj6TjEm9w9ATv5Cd7RhYTzshHj9UzQuHi9M5nULyVMutdYmhlIaDHcmIN2zAEYkhDLCc9zKRb7pdWyiF9d9GSaCyofE+1I/c1n2htExW0J2KqLEGnPFD3W5qo9LePfZdUmYRMiatNR6ZAuPtFXoZLt2QORdZjl0YO/k81pT8RBfFTa3/rfMP2wSO7/7ZxRreOem5rVAW17RaNAZKq3HHYbPPoueBpGgyYCrp61ZrLJGV8adcY/CzYL0jPmRYwBLQocihWBe/IGaEBPnxzhizFk3EcLiDzPrXTMA3AIU747EoBg6xI6/CmWlbG44/xcBmPP78pUnoOZfGnhUONcb2zPH8dpa/yjPlNbTb7Cf09xYiKTDDk3DiozvhdSqSjpNTkccx0QK6kqFb2lk1E+syJiPB7mYoMR2qxS0y8TcWiEaJW0wc8V7Bvr0YczNPs5SK1NTedQTG1LUjcrNv9u0blmHyaZjCXjNr6dBSjW/aOGFsgx2UufHTtreqDdNj6AePdR+d12NV242al4fcKOcFG3r+togNRuY2UHmEE9KiHN+cbjK1D41UtUwA8YvkRxxXXHSiABvtIL3Pn0N/A26I+/wyqkNMzHPL4ZIEpEGQ3gUCQEyIN8VTtXGWO59QkCttZxlSzyf85aZ3RgnCd3LNHllYRxCXLNFA6fZJDYcYWhd3Ozcv3BdfCzRhZ+G+31MfcqZVe+5pVIMffUHdQ8Dn5iRVBJtPhtkxfVOYtZiqPBOTJEy5HT51RI5um865UuR89MZOQ5bJ1mdpq9olC15b5Uku+oItJZNMeBwBC0hW4+d9J6I+2T/o42dhOYbFz3S09+9rYx3tIUrlxFe10wRAvURUeN+jwLLDHpLoc5OD2EvrNdrcUyVok+IIx4UMqmAhMyvuGWSgbWUpeCSmOlORAbXC7RYXW7gfff9mKV8s=
*/