/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   type_dispatcher.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains definition of generic type dispatcher interfaces.
 */

#ifndef BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_
#define BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/static_assert.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief A type dispatcher interface
 *
 * All type dispatchers support this interface. It is used to acquire the
 * visitor interface for the requested type.
 */
class type_dispatcher
{
public:

#ifndef BOOST_LOG_DOXYGEN_PASS

    //! The base class for type dispatcher callbacks
    class callback_base
    {
    protected:
        void* m_pVisitor;
        void* m_pTrampoline;

    public:
        explicit callback_base(void* visitor = 0, void* tramp = 0) BOOST_NOEXCEPT :
            m_pVisitor(visitor),
            m_pTrampoline(tramp)
        {
        }
        template< typename ValueT >
        explicit callback_base(void* visitor, void (*tramp)(void*, ValueT const&)) BOOST_NOEXCEPT :
            m_pVisitor(visitor)
        {
            typedef void (*trampoline_t)(void*, ValueT const&);
            BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
            union
            {
                void* as_pvoid;
                trampoline_t as_trampoline;
            }
            caster;
            caster.as_trampoline = tramp;
            m_pTrampoline = caster.as_pvoid;
        }

        template< typename VisitorT, typename T >
        static void trampoline(void* visitor, T const& value)
        {
            (*static_cast< VisitorT* >(visitor))(value);
        }
    };

    //! An interface to the callback for the concrete type visitor
    template< typename T >
    class callback :
        private callback_base
    {
    private:
        //! Type of the trampoline method
        typedef void (*trampoline_t)(void*, T const&);

    public:
        //! The type, which the visitor is able to consume
        typedef T supported_type;

    public:
        callback() BOOST_NOEXCEPT : callback_base()
        {
        }
        explicit callback(callback_base const& base) BOOST_NOEXCEPT : callback_base(base)
        {
        }

        void operator() (T const& value) const
        {
            BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
            union
            {
                void* as_pvoid;
                trampoline_t as_trampoline;
            }
            caster;
            caster.as_pvoid = this->m_pTrampoline;
            (caster.as_trampoline)(this->m_pVisitor, value);
        }

        BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

        bool operator! () const BOOST_NOEXCEPT { return (this->m_pVisitor == 0); }
    };

#else // BOOST_LOG_DOXYGEN_PASS

    /*!
     * This interface is used by type dispatchers to consume the dispatched value.
     */
    template< typename T >
    class callback
    {
    public:
        /*!
         * The operator invokes the visitor-specific logic with the given value
         *
         * \param value The dispatched value
         */
        void operator() (T const& value) const;

        /*!
         * The operator checks if the visitor is attached to a receiver
         */
        BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

        /*!
         * The operator checks if the visitor is not attached to a receiver
         */
        bool operator! () const BOOST_NOEXCEPT;
    };

#endif // BOOST_LOG_DOXYGEN_PASS

protected:
    //! Pointer to the callback acquisition method
    typedef callback_base (*get_callback_impl_type)(type_dispatcher*, typeindex::type_index);

private:
    //! Pointer to the callback acquisition method
    get_callback_impl_type m_get_callback_impl;

protected:
    /*!
     * Initializing constructor
     */
    explicit type_dispatcher(get_callback_impl_type get_callback_impl) BOOST_NOEXCEPT : m_get_callback_impl(get_callback_impl)
    {
    }

    // Destructor and copying can only be called from the derived classes
    BOOST_DEFAULTED_FUNCTION(~type_dispatcher(), {})
    BOOST_DEFAULTED_FUNCTION(type_dispatcher(type_dispatcher const& that), : m_get_callback_impl(that.m_get_callback_impl) {})
    BOOST_DEFAULTED_FUNCTION(type_dispatcher& operator= (type_dispatcher const& that), { m_get_callback_impl = that.m_get_callback_impl; return *this; })

public:
    /*!
     * The method requests a callback for the value of type \c T
     *
     * \return The type-specific callback or an empty value, if the type is not supported
     */
    template< typename T >
    callback< T > get_callback()
    {
        return callback< T >((this->m_get_callback_impl)(this, typeindex::type_id< T >()));
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_

/* type_dispatcher.hpp
HMipo8gH+ZrSjzx1ShxRG5x0gsjUFN8u88bcaoEtb5X5kCnNGJ47FuaD9IkseSP2c3WgXBZi0MfKGA+SpHcL0o8KeKZx8kzLsCjVf05PyCFdZfWq2idI4MQ6sOBq/6Ift2IwbGs5ULLsKXNvPrtUFLuGCK1xusqU0Ws6yO7Q6wxAPr6E/IJOZdsQNA29j4eQ/n5LHqrRl65n8OF96qC0vMwFn8KFGJo7SynN72HdmDdxIoZjNUS7bNa/owqLSqetk+prRZi/+bdgxWhUkRaukGc1In8MuqkIXRNQmz289J9LszxtpiOJunOvSiTtkIPIEnSpnmsAb344ZfenferXAdSnZFUIRDJEyS8fTha7FxK+gyWrAqCkr/Fj3HgPlyEGO9IfjLfleVgwAjbbmzQDCGe1immBpcOD/dAojMqEmMDK4haBl2iSusQYQs6Xijc7YGPjzj49+qh3r5Hkz2SE8QZJtSZj7tTBdx8lPAlDkuLoui3r0g48G578ly8WonxurAafUUZstuIsiP9/VkmWu3D+KSJOjmCYngCWxTC16KuoEqIZKf/+OTiW9MbQNIzcIhOtVB4yrd2F+zJI3F23PNyzJUhxdTjjqFqfpAJ74By2cHs77tOubUFcuTuWVEoWSiLgQtnCl8+P3gAPZMvyxf0Os8ZX26qELLeeY+fj+pPK09TSsdkWa8lI8ifCk++zmED/BPlJ5HhRqbaO4JqQE1ECzLoyqJcsDBWI+lqYqt33hrAcBF6qLj8bETi3qiGGCWQbsupt/0HRxVRXOe+EosTXG5DGd/CqpKMqjZ3fc+27wDZTFyJfcmaK4fzbfSxdTj8/vJVqPeHQehE4NmI0te4xrfpS8NaymW+RQz5ivL103GncD4eO20i/f60ClKaEIWeJwcwA6BvUGpI9dEpgbVgMAjWAH85BrEPzZs5ml30MHuWW6D6WLLJxw8E7bSxl6WZ37lfDe1oJ7vF4qpdMI9v6PTpKt57rQZoBBhokiKhRqjNv75TaCEOYXC5Z6PL+/caNFGnBquchFJqk5b+ZPqKktFPg+ljlYzKB7K5IwtvF9JMBtJ+1YB2nm8PCPykZK9oJWBSMGZE4aZh85DqAQ1ISgqnd7XVdgdWPk/ZMXtH8PTwZW02dVRZUrspKTWmTn5EOZaH1DdxhVdMZZrFkHJ3ImEtituHgqyKkro/+Tht+/332D7NP/AvXDZ+ozDxpvqFCYBSiwX3Q4yC2OMwvjk7524DgLbs0Ydx74lsraR+gdZ6eB5rKKZPtTjkG4CCJbLFr78RXaKIXrfPWc3FYwrw8E548jkl+H1D+dnoMFDM7XieWiUTAJ0QuJJ0ZdotaNTQS3R/w6oopDvGi8Ergh6XJ0qTs7OnLkKMD+Uv7JOE9GfpzAPdF865rvPufQLD60crgJ5+hlTXF9cr6sEvTqZz3BhrDlUu5MGgArIzcTg5+a2hD63EZjavhBLWfoluX+Tp1oF3crhG9tO97n5zkWKRJlPrvvdsEy4W9ufyzulvcuRLPq0JTHjehBUfg8j1zIwOeAEdwZIWeWFujsh6exeQy4JhGK8KVU+T+selZSsiPZH/UvcZVVRElUeGZOhXXIxjTkWAXqNUGt2X/8rBNnrooZlaMq0caOfQKrs4J7X5agpEFEnBKKb0KjRL9Cx6SAr1q7kxCo3mQyexYccRCpx6eo+JqW4V7iNqZb8H+ddbndtU1WGXIf3HB7bwK5U/GS5CMAZ+BtCr0y+GeN61DA271jchZIfxHM7x95H0lmdQ5JZVyqei+oNNfVuYsHmzyoD+keTVAqMkoEDnc8D9ajU5OGGg0jmwHUWqTVBv1R9MYD7rB7X+U8D/9ng/egtfSApgIFEVV2Vxl+ZknvsIQhsa45TsVUPDNNcgo6VDabncACSz20wwBJCP21i5ZPOsp6QL9i9Ec05uOzpr9kpUDoTfxYb0FGWkcsBCTD0tfAcV6znN4CvoiJwU6b5JBhf6+vO8J38KMRgE434zBW49Se0s16438Ywwe/xPZVZIKIC74HTjhdFoMOpqdWgLRFQihShvUmXfYxaUpVnM8hULauTdfT8K6gAo8pa+sJSCCdyS8p+8rRnUtr7Qw9hKr7mHv9k9iInwiBgGu7mxrWzrUjYJjq5N6Ukb7iodJ9ad2ekzFaLnCU2JIZo3PTBI7E1uCkNVjorCDfxLXA8SbClFBD2AoXicCSHeiy93SFW9mhI0NuCtHCd+vBIWSbzg/t8akHvMiMmEVefgSMRzqMdA8ktTWbN5MAoMd5RzdQ7pcx/2BtVJz+gg84SRsUFAJDFv9RY4TsjOWD3FofYk36ebp4h8o8gzacvducIDK2yyKapsM2KdzgEYbSr0smxmQ4Y93v5LvgfV+kvxUwwhXOy8eAkgtYgKrWAYKS3KvHr6zXdORlmrPqUjblgUCnyRcdsvSF9ntNQKAbLljLbTZuGaiALC/HdwiQ7NRDlpi/760UWt9RfmhxHywweWcUHTQmurQXhzT9zo1xyiTiYGncPkhJ/ovPFZdRfKQrVpPxjxU00ybkQQlngwfwbVVpDVyG+zPji5TOHNrXwZCBwZJd/0pqGRSwAGx87yEcZxBPuyTWM3CkMiH5GyanMqWFgdndzijWhmkkETF49YLQfpNInyouUcRF0CA4xlPB25zgSAERjqeeg7sGRUdKWCCmn7FfGznM0CqJpGzy8sLRliYVFr+eQwLP5A25fnNVpvA93108iSLJOKZZf1QwsZBxecdO5LEdDNMFPKI64EboTlMVA8RgJeP4XBqTjOwFHHv6d6asO5nyEfDzQ+95qdxOXoQH2BGAZyrlxAaxSKO3TbUOJcahhvF8ReWwfe62KffsX72mDGJ3pxqPMjmv6W7CfexPEiFkkGuqvS76rt5e4zwRmECnYsP4jJlcbAQfHaTDncDBYJtiqykenX357chR7kFFnEsdorMss0Azo+iBjo8WFPqkR1cHboxGGsz2amJTqWawOAAvvsm4PHnvineNNlh+R3n9Dv7KULeswFTZVOBHb73w34E8t5DNb/7F69jntiSZS/J/gjt5n4+0kUoSDqo+++rfiY89dlbxsJEVMOg50U5wI/ngW+1SwOlNc7qGo69xfUQc8lLu74souKTUJboYp4+gC3MpWgNf1j2AJpqB4i0eR2aiYRJ5AX+vTYki8CcVh7opnYBGqXwV+VSmW7UZQvh57P5xPInA0valD1cIeKvL/UE9Zygjez8M0Zn7IwYit5QVAotrc2Y4/VsVS2QH43+vtygJLpDvNyYkllCCmychDc9Xb9I1Ap5Zald+ey4n+9JVzQ2mOi0ReGfmyGMAnA2ZFDYOxUv4rMA8qtVJoPxZcut+9+TySgrji8HOC++K9J+glFy2p4wo/b3SePdmYIhbDIAWDBw/hvjqpExphjkZ1VjJbrkHZ8T8W6ctIIpL5mDvKLlevRowlxXazpu80qSN3T494ndTBQItHhuGDaYOGp61UWKL3SLnYmC3JG2ioyVb17sd3DQ/SLTQW1wRM0kT/n7DtDFkbuM0QLXouz5nHDHderJbaWykqHT7wkiYwVGFbv/+h2awvJFyMShX8kD0ihHYr6BxzSZoSgsPCokJMQpukeA/iGsgqxB8wCRwBSid77RFbJfP+KAnECp2hktOTe4t4xQ/po8OH8MaB4KsZxf8qmX73LCsi1TQKw2CGbSHlxVB3yokJ/+lQmI1pc/b6o9ug84DZeyZYZ270GBulyJLE2up1yzf/QvksvxXCID3YwzE4qy5/hpSVA4CAZ1dzHPtQcH62R1Act9sN/5i1Z7OARRemk28ot3FU8OOH653R9fw8IOV1tULF8wyboI07NaLxlbZKqHxXQgDIIP39syDnGJIB8/Ih1VTHiSYFK5X67ZGLUwfNEuzcrwSw7k1JD/8XsdnSsxz5PtQxY8AS8j8yqDejgYjaYqw1cJRQX3YRtTRRBrk+pzqj5DCHc8lEH3QwZhSNz7bhznPfPD/oiD6upPNcuM2t36qjWQdGa48WuKlSvuWjAJ35+xPrZOxisaZiSey6oJlmUVAI94Nwm3i16IGjYzszgOLclIh8/KfFnic767lsnzsHG0Q8qVy98R+11PAMi+oMC7yGcIEyNOsIQYS9cBnLAXddN2dlN13C5Ld0E9aZmLJlXB3W9SPcVlKeCNi0P12Oep5vFMNZZwW1c2nupb/e5SKT1kpBAmDRHAqImVgoxRk794KbH5ZYjbVVJjY6jNyIZeyage/siOQ4+KuFmXV2jtcW4I5MXLA1/Kw1wxbkJvRHKdt+XCff173/jIRBQ0OB4+BGl34I1h4PRreYaje+O0xsWM/Hes69ua2WnVzSYq7M0msAmmINIMY+MtF0xG0KRQqISHUz49wRQLz+f8PGNv4eCjqIeATF8ucF8LIT12akddWLlQWZTJ1x5vAeOeWT+5Xj+pHAAwioc5fbGc65iB2n2+AfSD0Subh/ljZVxb7zQ8oCO229T/JrPIeNTJqR1M4ihNEgd83Hl5kM0XQtiWTaABT1knxLJvdD77Cu/YtI5UJx/k5s7/B1Sf2908W4y98uxctHcH8rHRix6+obS10rBhuAzW3psBXtUHHV84f3aGtX6TEPY64nU1QTAzl9ws03jBOPOnXcuXIbHX/G++Qd/uu9xpBfgngbaDKPTn65zaf06G+RaFdkzE6wpchqm9ypY6bfylND0T+tD+TnfvU2DuBYjqi4HTRiRBJVNoxhoJFcot/oVnUPI130VYnv9vb1uH3eH3yUuW+lg/IE0/6n4Xvkoi5Q98H5BMuxw67aLhpr8XjWE1k9WzcvijYtUxsxbkaPaFAAfp2jPqDawiwVQVep99uXBk+pZCgil0mqUCcQldXR6RP6mh06GqrX/LIb92RiPty/MpPoNmXvQdb3RF/lnaojGrCsGCCoa5/0O/CIfgJB7h2wYHmja8U/GpzcN32UO90AJ6g9ob/QjRO3R+0CVIMMMlMQRreCiE/UpN4AAPVQUbbsw+Fpkl80ypjEy3tGFSsWlEmtg6mk7TDzjfl4jyAnTiGoLLNlRx9NKxo6wb1KxcmuDJS6/V8cZ5IvyKMLmOK4YNEOpTy8vOtHYYazx5uxWukvvE7dzEmwlb3UvpjPsvPlEtO3bkLNA2nOJhlWNnYoQQdhfGCAqOqSfyBYPLv9o0QouVPDR2CEQ6BCRid1mYmd7p58zLgx9L+AqT1WJCVevx73ZgNDHvM2OYIuG8H2iDGLu1rkIS2Qb+G1/In4awq4Iw1F/HmXq9T3ph6Umdv6i7JrvYx8kYWOVhaqM6CMp2Qyf8qnhPTciDmz91otyDSlwf9zuG36tZkwRxKzlglHbOQfr0mfDkD8H91KCxTeVy565Kt13kEXwySnb6Hx544/Y17D2ayom2Cr29mim/EQdRHlaOh5sPquuleRZK13gN0YCsgC5eT1bjzDEeuhhoRp5GOnhfbM6a4+2Tg2/TeInTbAAM6XqJyzNJ2iK+LeQh3pOUc55yqivs6yK0/3WU3fnSl4j3R/WqkbljAa7egnmSqNySMY0ptJHL6ZgUBOheyGmYPDu99Gid63taxbJU7/5Sxp4PVkUrh0pRm/hM3EOQMDqzBuCxbdv2Gdu2bdu2bfMb27Zt27Z9p/7V7aqnkl0WqerOu4mNSqykzGP+kV6X+OCSbmX115vcnXTyf6xLEaxt0jP9QqLFg1k5xj0VT2PaQz8/H/Gf4hJr2GcFGfSyyYxPe2TJcR0dvEBlVSdmtisIBFDWHMiJF5dNhj5vSpYg9JUTt+HwM6Vpg6g1dAnguEzDMJP74O+mjpTKsFpsxkrf1kFLEIZxhCzL3R1H04mzSmTAvxAUyFX9h05T3sL3Abto3834k8fTs13OyxDKS+4dyAxFmy9rl+oIaJLVLf/s/5XNEeN3pUAGpaI67FJ1g9nMxDvoNPix5wyNQTmgg8cGSe66KQMKV4eHFjY8uoxFIjmRtTnwvaTwt6tlKgOE1MawYSowoXnrfNH2TIdYzj0C+XjJvzwIrMMjpwjOd8QKz27LhENzflTBSHUEQOD9xN5gYoTvcYFU79qKH2kVtuE9wv4Mh2898q9/Y4XY/3aITIlnEn9j4/p5SICDwjhacdcRE9W88XFJNzGpQVa6joxW4/ONfzBVa8UIG3plhHqaYsh1tPScQEay6KCRjATsIy6Kl/KaWTymtufgkbFP2NTt6o8WiZIFVKWZJbfUapEJqPOtUMPFFKKO9YBc275RlDxsQJamIg3i0Z8X3KLdNHIV1bBGjqXN5dyHYQ5CRatZUWXvt9Uuxa5oT6hxnWazkSUJOsK078zsspPaSP66UFkRksl3TMRNqi8ifOi9hZys55H1wyEadG4XKFljp+ogA4MEieC+6XlyK4sAO3+8U2dLg69wQGqh+PFlLX07YXp9T8DVObHy9DhhCnjDv52FojkDCmFe892NWPKcOdNRwPiNwHHM63dxYYGTN0sNqToo3dtqsA34hJnWLrTDh8Y0f2nINT24o/Iatw/2zyTRBEvha68EBDG5JgDCHDD/2xpAS9R03NzD/t4/lmm6YBvt5Tx83UgqSjhyQYOYIHZ3CJ1sDZnJCnQAmF3/b1H+V7Ie1rnyuiM+qal55TBX0Ao/kWNZ0TPlLC2rJAKlOSDoiYmsYVfW5ibC5yXMz+Scm4/F0npjQvuQY69FVJjP04LbR3716v15gMetCQwBMnO3NlgxTNAUegZrjSpeN9+pfQXK32FOXOtnKyne/Iw/XxXpIXpiVt6nFkw6/QebyXhUNeaK0ybdDuY9tmaZxz94faK/25ENeXNcLfVg+0OI2jiJ7tPWXaLvbLe7oXcY/5lTQIbf7OL+0zbjpC994UugMRhzW6UpzL9W67M+TeWWO7I8uvxif8l4LCX722ZVmCfP1M1UCezYFNxQvA97AXtz90ZXJtLyNZtNUlqNs+IhSD/iRJIH5bGp/cONsT3MamYQHSxhURyolHE5pAFDs6fbt00USfAVLN1hRrQR1eVrcU6fX/tnCpqEgI2kIquaq3sRQ61UPiDsGFlWxtmWMffRJh4e8oAJ+1/4KHJbtVvRcbP5ZpjrYVGN1Qsmhrh4QJ/ujqpyY4/57fH9ySRdwsBmq8E91iQ5S07IIRw7PxZfBD1mTa90hA+ZANUX2H82baL6/Hav4tn/Nkndg1piVE3vto9K5+1eyRQZXjZqXj0dxxD5zeH/jUTEu9mCanBWjjbfD5rTXHJmfW8S9vJ0BHAnsjvHpA0+Zi9+JzeRzdvqB1zhslatNu3wvLP0OGnz5AuCHb1NqAluX80J7S1O/ssV+DKwZ19mW7fuOrObB2Q9GEXVF6SDfBHqSR4AHSn0ivL/IB4BpfbhAT8CIYwo2gKeHqKiIjQUaJnXfPDfEJcAMgnTmoauAa401/BAXx7f7ESjWPOo3F+LTDBXh4EQCDxKfRYtshu1oB613rJQfnfYPniy16Hx1iiUcCe1dMrqFfzc7TUiDBQaD+N2ojleMe3+wbrMOZaaViYCuRJvueUmQdlk6frAi77zQDacPFPzH0DxAAczg+DfG0oyBHVKCmrTVQNlZoa7oDChfjqp0RWfJPR5CyCSC83SHnq5lNjrEtEvjkISHvMGtPOljYsqL38L+nmMqjn3wbGP560iGpnN/L4kogAcb+cbSyRbQWfF4nMTNrZTSjopKJYl1T+ZW13IC/rdyLPof8/9oDJy2+qqCDswoT0AM76wsTmpXpueAxbZnZoEtzget+87EjW8zz3+AMF2Reyz8lm9SFoJjfoYTELV662AP3vCZ3pRaI7s19z5VB/bCYR2je+L0iHMewdgbhv5wIY71emMnDkDuR/oUMtRKo6PRYVg18tngcwwdjrDyEsEL29YTVWmNJYsEWb3dgUJw/N1NuoTfLFWgbF7Cp/JUcXRf91m3HuvUBhkf1G9sXefdMW/NULMI1h2sbskt/DbqLK7S++KVyfO9o0dxDmIi3ogALACNNgRF1JE6ULLxxrMV2lX08zt6t9adXu8jqfigCR18RJ9SO/3ZZFcSDmHFF6pR/ZLebjJu858Qqo2vCO5yBDN4SSIIy7sZ2yyqp6Qr3d8clXZ35Obx2373i3pOb5K55L5d9sxh2YTKeVkbD2H32Ha5Ke3BoV5SfrWeiDywQXzj2NoBH+1lPC0m7J8TW63inN1JZBvdgywLCJ/2si9g2W3rBdGWHIwrwaeKM+oaIgOqZIuMDSh3TgbibKcSkVvvT1gGIccc6ttOCDmqhkgv8+O4alFhedDmUziOnyw5+t+EfYBcYBAmBE6ueMD22ItUWAFKdLXPj63d4aLrzvuV7jW2wP05GZeAn1o3iC4y7pk/OuOAH32LWuj2rvK8nVnbCwE9midZKIRVwejaBT3aB1NxO/y67hQNta6AYXbfOZfZsLh677Xk0iINbbzxBu02fAppM59Q6LaPqTrWQILHut/Wz4HG7uFAOGo7gAU+QKaL0aM/XzNhyXK4MQE2cCLb5PwIG17gD+dxnfaaa6Bm5GHHnkWv8f/fH9+sklvzDG/HN7IUSplsCAHsKeA/bJCOCTu4Y131eKUeoaUfzbhHG8GmaYgfgxQmqPMrBXiJQRs4uSiU0hGFjbbDwcn3nFmaah0O26qeCtKeC++zXaNXldr0G4iPwP5rBD2D+uVy4BwgX6tIsVBEMTIhCB7DJna4X2Rbfjt1ZGAjh3qD46OHXTA+Dwlg1IgDvG7oI1zTbTD/1MDKI//Xhewfk86a6gg4ulfghd7P/42AwYyoPr6xruMA68/CIO5gUmvnR2GwUvBtpjpVG1imsaw5/x9zhNRxTJg2Xo+eCh9VA0wMOkcn4m3PUTWGn6TeZRw4NvwQilHLHFG1TlCMH1yzPsOXoZbiXzZhKLOh9ynHdxgtcL7WDhrDvQKmAbmzLJMLDllWUIH42p6GUz5z1sDFtAW9lziBtlNILDHwdO+m/p7rnCUYHvg0CJVECfB8tGt83G/6nasNvXSLLnCXLChbq03a7DKIMXvv3szHNnxiiKzQLt0jcvB5EtPtoZKdwVaVOfPmPflJuZBJwXhHNYbrZaZRcnYqLi/zGU+yyOls2SafCjT+RbW0iLB5m/HXUsRliEZx68TT2Bbkrdd4B4TQ14p6/NDiov8q57mS0uNKO6FG41cZN088gLzvaogsLM=
*/