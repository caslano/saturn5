/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_mapping.hpp
 * \author Andrey Semashev
 * \date   07.11.2008
 *
 * The header contains facilities that are used in different sinks to map attribute values
 * used throughout the application to values used with the specific native logging API.
 * These tools are mostly needed to map application severity levels on native levels,
 * required by OS-specific sink backends.
 */

#ifndef BOOST_LOG_SINKS_ATTRIBUTE_MAPPING_HPP_INCLUDED_
#define BOOST_LOG_SINKS_ATTRIBUTE_MAPPING_HPP_INCLUDED_

#include <map>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/tagged_integer.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! Base class for attribute mapping function objects
template< typename MappedT >
struct basic_mapping
{
    //! Mapped value type
    typedef MappedT mapped_type;
    //! Result type
    typedef mapped_type result_type;
};

namespace aux {

    //! Attribute value visitor
    template< typename MappedT >
    struct direct_mapping_visitor
    {
        typedef void result_type;
        typedef MappedT mapped_type;

        explicit direct_mapping_visitor(mapped_type& extracted) :
            m_Extracted(extracted)
        {
        }
        template< typename T >
        void operator() (T const& val) const
        {
            m_Extracted = mapped_type(val);
        }

    private:
        mapped_type& m_Extracted;
    };
    //  Specialization for the tagged integer
    template< typename IntT, typename TagT >
    struct direct_mapping_visitor< boost::log::aux::tagged_integer< IntT, TagT > >
    {
        typedef void result_type;
        typedef boost::log::aux::tagged_integer< IntT, TagT > mapped_type;

        explicit direct_mapping_visitor(mapped_type& extracted) :
            m_Extracted(extracted)
        {
        }
        template< typename T >
        void operator() (T const& val) const
        {
            mapped_type v = { static_cast< IntT >(val) };
            m_Extracted = v;
        }

    private:
        mapped_type& m_Extracted;
    };

} // namespace aux

/*!
 * \brief Straightforward mapping
 *
 * This type of mapping assumes that attribute with a particular name always
 * provides values that map directly onto the native values. The mapping
 * simply returns the extracted attribute value converted to the native value.
 */
template< typename MappedT, typename AttributeValueT = int >
class basic_direct_mapping :
    public basic_mapping< MappedT >
{
    //! Base type
    typedef basic_direct_mapping< MappedT > base_type;

public:
    //! Attribute contained value type
    typedef AttributeValueT attribute_value_type;
    //! Mapped value type
    typedef typename base_type::mapped_type mapped_type;

private:
    //! Attribute name
    const attribute_name m_Name;
    //! Visitor invoker for the attribute value
    value_visitor_invoker< attribute_value_type > m_Invoker;
    //! Default native value
    mapped_type m_DefaultValue;

public:
    /*!
     * Constructor
     *
     * \param name Attribute name
     * \param default_value The default native value that is returned if the attribute value is not found
     */
    explicit basic_direct_mapping(attribute_name const& name, mapped_type const& default_value) :
        m_Name(name),
        m_DefaultValue(default_value)
    {
    }

    /*!
     * Extraction operator
     *
     * \param rec A log record to extract value from
     * \return An extracted attribute value
     */
    mapped_type operator() (record_view const& rec) const
    {
        mapped_type res = m_DefaultValue;
        aux::direct_mapping_visitor< mapped_type > vis(res);
        m_Invoker(m_Name, rec.attribute_values(), vis);
        return res;
    }
};

/*!
 * \brief Customizable mapping
 *
 * The class allows to setup a custom mapping between an attribute and native values.
 * The mapping should be initialized similarly to the standard \c map container, by using
 * indexing operator and assignment.
 *
 * \note Unlike many other components of the library, exact type of the attribute value
 *       must be specified in the template parameter \c AttributeValueT. Type sequences
 *       are not supported.
 */
template< typename MappedT, typename AttributeValueT = int >
class basic_custom_mapping :
    public basic_mapping< MappedT >
{
    //! Base type
    typedef basic_mapping< MappedT > base_type;

public:
    //! Attribute contained value type
    typedef AttributeValueT attribute_value_type;
    //! Mapped value type
    typedef typename base_type::mapped_type mapped_type;

private:
    //! \cond

    //! Mapping type
    typedef std::map< attribute_value_type, mapped_type > mapping_type;
    //! Smart reference class for implementing insertion into the map
    class reference_proxy;
    friend class reference_proxy;
    class reference_proxy
    {
        mapping_type& m_Mapping;
        attribute_value_type m_Key;

    public:
        //! Constructor
        reference_proxy(mapping_type& mapping, attribute_value_type const& key) : m_Mapping(mapping), m_Key(key) {}
        //! Insertion
        reference_proxy const& operator= (mapped_type const& val) const
        {
            m_Mapping[m_Key] = val;
            return *this;
        }
    };

    //! Attribute value visitor
    struct visitor;
    friend struct visitor;
    struct visitor
    {
        typedef void result_type;

        visitor(mapping_type const& mapping, mapped_type& extracted) :
            m_Mapping(mapping),
            m_Extracted(extracted)
        {
        }
        template< typename T >
        void operator() (T const& val) const
        {
            typename mapping_type::const_iterator it = m_Mapping.find(val);
            if (it != m_Mapping.end())
                m_Extracted = it->second;
        }

    private:
        mapping_type const& m_Mapping;
        mapped_type& m_Extracted;
    };

    //! \endcond

private:
    //! Attribute name
    const attribute_name m_Name;
    //! Visitor invoker for the attribute value
    value_visitor_invoker< attribute_value_type > m_Invoker;
    //! Default native value
    mapped_type m_DefaultValue;
    //! Conversion mapping
    mapping_type m_Mapping;

public:
    /*!
     * Constructor
     *
     * \param name Attribute name
     * \param default_value The default native value that is returned if the conversion cannot be performed
     */
    explicit basic_custom_mapping(attribute_name const& name, mapped_type const& default_value) :
        m_Name(name),
        m_DefaultValue(default_value)
    {
    }
    /*!
     * Extraction operator. Extracts the attribute value and attempts to map it onto
     * the native value.
     *
     * \param rec A log record to extract value from
     * \return A mapped value, if mapping was successful, or the default value if
     *         mapping did not succeed.
     */
    mapped_type operator() (record_view const& rec) const
    {
        mapped_type res = m_DefaultValue;
        visitor vis(m_Mapping, res);
        m_Invoker(m_Name, rec.attribute_values(), vis);
        return res;
    }
    /*!
     * Insertion operator
     *
     * \param key Attribute value to be mapped
     * \return An object of unspecified type that allows to insert a new mapping through assignment.
     *         The \a key argument becomes the key attribute value, and the assigned value becomes the
     *         mapped native value.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    reference_proxy operator[] (attribute_value_type const& key)
#else
    implementation_defined operator[] (attribute_value_type const& key)
#endif
    {
        return reference_proxy(m_Mapping, key);
    }
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_ATTRIBUTE_MAPPING_HPP_INCLUDED_

/* attribute_mapping.hpp
A8Q2u6qL0RqnxoYisUaS6GyrcDwHSnojFRXZTNE7riH44GlglACsBE2y43F5NUdAuvXWSF5m8FofVCTq567KaSn9AC84OBiT2HRhh5dmfNYSUa+0HvdUx/Uw9i3j1f5FVUrfdVA1FnEXH0Iu0ZlfEKuyqEOejKGih+Dvowkkw71IH6IFB77U9MxR1XArL7jKcwq3xEiu3Grezfx+3ZOiVH57XVwVudCZvlDa9ckbjak5IVh7yepk5eqkfwPFc3Y5ixycAuF0eFedR7DCMbOl5rXd9Dhl95aFb0r5SIZqYMuLkgQIGkMFsuRzO/G8aqFGBIxUFIJoXGRLq3xr6Dm/0pWnEEVYBn9l/ZIQdvUk7n8b5yAYwFa+jjNDTmq2XzIzbnJjweeDblgZmaau54Bz+AD/oFwQikPq4ISHWT7lKnbH+7uJwcSzfrBqCysNFQwKAWMNlSJdTvM2Jaa5/rGxNx/ZlCelYc7X+MY/ePxiOBNeuKVd0I/wq/mgwzhaKKX51/43l8yRMCiZKWj9GfUZ9eE5WtvYpK3oKkz2Im7utmw13LudjAisY0kNqnlFIgy1/jtRFD8qJuVOzvzjVcuY5feU62yMUmqMopalkzVKaaslZmt/6/LFNtx/CMiK8816fuzf/l+NovZzkASSJ74yxc+sXr/us5AZwz7PCxxDD2K9iPYJk8yUN1yQdDVfPWILHwLSSjpTxPRw67KNj1HQppdpF3NGB8RbO982k9+WBsTzUpphEjhRKSvrKKa5D7WxyOoxfBhGkc6KEHw9UyMMINcCvf4g7hWDwTzbhjZUrREnwzm1jiZ1yVydfdfkzxHJAZfU2l1Pl3quwhT5NmyfJ9MH+92QGZf6htvXzJKAet6qIHRXH8FwB+695gsVaC2yMAvYGVBQmq2LENQ509YSIiFWZBEA0/daos9V0agPggSaKwtxKbaDUq5OShpPNyHSFZFj1OVx4pMmmaWzYDXLLuN/9yv4PypGG5V4E2mKjmBXt5u74NnuiUsNXz8jkWIdBphFn0OgnTSbI+vQ57b02+Fq5UHdJzRI0eVDZTXoxKovAQFy83GJDc46XURUQ+RFxt4cXIzEdzbY9wSfyql10VJZzGfgw8vM0ERCRXFhLzS5J0vMv4Wwal6oJQvUInpAEv3F7I5ap0dXG0NPWp4uZNDe6mGMel+nuW4ZAAQs+9OzDKYoj6xZo4wy9S4EUfsV+1nv7UJlj00yHTIdB7+gFGOFEVQzojWN2B+Iw77qWhLgeg8kh/OE+OQDn/AuONpw3oNQHhXfwHbsS5fXsgdrBtbvwFhY7qUQqiIRqInBMJFrYEpmOFiWhh9LX5ZpdTgo17lpC0UJOzIjqAEigIvsFvzMLeXUxiAxL80hCWr9hTOsfeN0szI5qdnYaQZiUxcSxWYY+XHfkynsLGTeqM5VPUOFdOP8qB4+6Y14u/FY55IR7nIMyS6ko/tXIEtqfJw2Gcl94lBN6iNcVStT9qFcgO7CMUibkFmuCVmB696FIExFKPbNaVgzC5lNZUbFpBME5cwULbspCJtKKVTBjTzFqBb1TWLJ7Q7BNopiBf+Bei+fqv1HXnzBacDwpcXo4Fazp3Z7rLy3DwVrAonbkgfU5tdCz583j4cqVJzwl4Ak07/rWQyPY8YGQJtAkS+iuZTw9izb4Az8L/wbVG5kP+L36ak8lsbbcAmgHxSxZievBE4q49wpzV7OJiU56QT5MSdMsxIVjwhWvjNXvkeZJbya9y5/H/Nx0Sd/q3SgpHb09TQBJSRUKlsvzKnXDAeyCnEcuCCSrj2//L1pd8RhPJwWtBa3sc39CVd2K96PJYrQZ/NtJFKH0zEfJcOCKyzsu7vYGv7uDu9TQuju7x3zT23Pps1OtMVeEvfs3zKXam40FKHTKyHiRC3zLcUCcArHPJETVs0rfJCP8LpoES1pnjUnyrmnmJbaRzVz5WV7u+X8JcZLlh2CBHKXoaZckCsD/dze5h8D5o5IzcvCFdGa3NzlPYKGfhdL+lZnf/sjjgq6tf1g2GXcqwcfwWFiMgUtqfLq+Eu0OZpTX5rWYbjUOejVyel0MKT7BSlk16mpplabtYZqou1SK5eK4FIgmierJaF2pi8n/VL110qvzJ82Fp6yMYUDXM07t8akHX479uahMjXyd3LuL1KeKOqsU5t5X/NpqAkl4prGh60sj+hzhkbiwt/dpJdz7fVmDjEOEEj/mRlG0Tz2f8OYvXh+3tS6oJiXM8wFRe8uhD3YOSwfWG/zhbHn82A8HRtemS2G9UfEkWHPb4wgwbyCkef5E0sfSl52e+WcE5R+6KUwAtZwQoTTkkWzhd2kQJfn4x7hmuVibIW0oT8j22W/0cFfrrS/3VIrHyrxr+2adMc0NhlESiRMcXKFcUsfuaAPn5j3lUpdIEockel4UKd1yaqsG6amFNr7HRx68vseFfLjFfCd04uOjVRP/wXrfWoHK6618w5GaK67be4rjwhccW8vH0CuoJtTgjiMvmtWB+59h3HOQrSFd7G1FNbv8Px80/WfsnOil5C9tD5Ttua7h8nd+ZztxshGwRaiBV7LOYaqukddpyGdqJ3/txkzHlemqDilm8+wu41hFnsbaBi0pMfSZbwdSu29guTVVOB6UrrB8Aq9cZ9fY9IMDIzuzEDpgr36wgMx+0mndQD4NcQHtm79UGzAxuGuKox8+ebrGGe9t93d4N/beKPXdPObfYNUzh6Z+WYp9RHhHe+1WBfPCn8ssX6SnbCLA/CNuSW91ZEPaaeCxDr7rwnBgOo4vuH29VaDgbfYwjpRcng/DafNgaUrIIaQNXAirg7OblAu0wV7RoZrrnopmsNzlpraA+2ah8ExX5ILUjkcmjEzbkVx//rFUsbxWrOzdf0sdJwvNTnr+p/tXas5k7nPEWpYthk1K5NsKqXLfx0o6QOd13l3IDaPS8YFQAEyoiqdaNcvYBbbg6BXyL8sL56vxrubgbg8/mVj1WayaPp81lz/PfSdVxySZcreuJc+dr80fpbwcUbZ/hhsczM+OV2eBxR0irVTKFhP4Nwz2GZWAjZC6ZesNiiWfjpVusZ69+KelV6r4nhFtGYvsoxGk8ieZdJsS0Ydtm887TV6/FdZmY9Qw66yvaNf2I8Vck95yRY7kW7Hh8h38mFQW2V6XezWuCm+F22/pLUso/L+eyaZllJh4Hoaik9ZOpVcrWUj1XrhVOn9a4HfnFnI1gMVvuFIBIh7+3SrWitlPQqWBoixa8wbh9rFw54AKu6bBk7zqoDzwKn6vtC+VETW0IF2kHMFvlTNMmoy6wKLb3nq/zGQ2Ln7rdQwV4xX+Ona9rhp+59SbETkGTe9JgCjZGNztmddYzpTNboVCNa1J2KO4G3mk3LtxgUfYveaj2AtUJBBVieEaOk3pBmBc+l3mOz4uQ/OEaJKNwcT/prJkPvt+2Fn01Su9ytA85zvUjIABKOybrfof9A+rc6yeyJN82E3TE0x6AFSSi6WGx6HIDi3OxXZXWE1X7doCNBfHGwRBJymZCkKWNU5GqIkOD+PB6PmPb99GbfJuB3OGK0pQzMGJXh9QBmnHu5s0/cbPbNRvIRa5oDXRaBLJ9v/fELIVB162NpyUmZxmrwIV3fL+aJDOYxhagsJ4xi+IMsXoE0UVye1pU0JEFqXBLIClq+yd4h2yqxbfkRL0J4rVpT8Ve3g136qzY4QP/TU+eeSh9xsMku1os3VBu5ZeOYyu0PO0OGq4rekVjA9JOFs7VnK1NH6bZpmrsLbz1mEA0UqIYhiWJ5qmkO2VjA7tGrykZT/pcyBx5lwaWffmqDGfYR1V0RiyvwS6Po3/3fj8h2LGjM7DG0mw4I6Q5Cy2RgPnBV/9vmE3xGvOo3gntytLZrWPll8+HWc4AW5M6OThmwDOWpM2fXYpE0zLPqflkfz04WK1tcW3nxkNFsi0dFVK9sili6NlrHZfNBohMZhMdpWGWWaU9dnvrbODt/FhtKKYnjMwENeq9b9ZppTnhV/2x2CmOP1xJUSA0kUDw57DVrEuDlTvASVq+RCiKLvMCfho6KYsZrLHP0E6QNHolYK3ESiXE5lo9V6gtIkHlsRxIxFRI+mavDieeWpWvPxV4WPNIcJj6oPqboZh8heSlKcMfUy12465ypSPwuGt4tBRlP2TyK1As1/zcS6Sv2tftdbNsgzRnvUqGLLnwQjYQDSdR/oe/prai3btPlWI98VcDALP+n/DXERkpoo8gsnm8TavX8T10bQg0AVKVDNZIMiuDQX7Ycqa6peUPRvBWMn2+WnTY4vmR7AJIYFjxJMNsx/zIQd+Br7tZ3Qss8ClwOpYC1GVHzGhEQz9X1ZGy6nBUaT0CKWmpUQ8IRmSuGM7Eveq2WUSpBIg0zy+IKM9A5Ath4TK8f9Z8a5v8pOwJwsMpBGsY1YGze75i8YPy46T1RmsS0cwbuNjOgiC4TYIU86KBX7/PD9tzegI3T+RdYrIQtKYity3vpbF/lwT2x+kjafY5WcSCbRGY+lUZLLTOKEf0C6dc978DDWQ+nMUEhyBBuCJAtfLycbHmf6jT+8L68z1hW+zQQ4aY/GotaJXV8Z/iUR3v8y5xFRe/XeGHrGEWup5vpSuZ6XHTXSdK1pnQnHVrjE9utq+ImhADeHw/5T0bWeonkUAV/S+r61SJVyN24CexgzXUaBDZ0u5pf2Pk5LEr4YOhkMbOxG/VaCaTxPH8ao7zGcCxwW0XD+ugFw+uUo1ntoX6hcKPZse7otlXz97zxH+hyXcrshx3prAKJIJLoVFmMf9RirvnJePQehU857ij9Xsmr4ynh+Faa1fkDJA2quUqYHbe+2drUJaRLQQh55Px96qPD1Oc3ZEBsIf8vkfa2ZgHJQwLmO3GdfafEslAikKCbesxKp38UbLcJg7ukEg5ILqsYq9YdzeESzqzHgqSGddXU9vHh3CoB95t5oC0MZzyU4Od5h1UZfjuX+fpZJXAsj6YrLsHNFXoC1ABhqUSOUX5jxfWzU1MEBJ9VT+KrMAL0goSNT9OH7N/71htMJY/s37bZRW7hhC2jUrM1iREV4cp0zmyH611QCotjqb8y3QDP+y7Gty7lpuK+IO7sLXTy7m+PwqRcTgI2cQn+iCC4sJqE+Mhf8tgAlvunFNo/1TuDTM1F5RGYzqqU6x1ZqiNu395VxyXrlyfXKehFuIvz6F5P+rorvd1LEY5gbKYMx39XCm2xiYNhvbtsEDDfKk/ZyYreb3I8nWDv08XghRrT2sS/N7/zqwNFrtchAR0NPmSKvimk2hSTuTmgmGRV5j9xYrrb3WcVbw7xKE7R5OTbR9Ej4EhPduCif6xwXxszqm7ky9MwOMKtMhkiA7bdpF1h41onSbepMGENWXCoYvieaFr7brSiance4P5GJFYnrHCZF9zUmDdL6btli7mJ4Q8mkuxLiuUjaw9QOdO6uY9BkzXgqnRAHUnDx2Y2KCliBQqeENBRMd+zY9UZC/burP/5LxMpw4lkSJIaZoN65Bku2DiZP84p7xRRsRKIdu8orEjvck+kxtUbnxjHkUz8zw4tycPzvv8BpJjb6ij2rL1VOOEyq2zyspTetpbdMtEVMcORdbHR+6Rjj+Cqlqc/vd1iSzpTHAc/ZvQ2jbFuEzB2jiaOr+q1nUz0o3zfX3eJa7NgSZtkurREtUz5dPBXNV+oJupxPd74d34V0kp97Q9a4Y2smRx/U6emsXGcACfOm5YVQ5H0hWdOSjR67RRAfEdAfACOT8klF+PXw8ju+VAh9sYW3ttKjDAa7/2oxhYJOd+TAptZ4zagvmJ1t+LEEM+2XlfW32IcPqdZutRBaP8pPC21FUyVAkG2o1bZVWm32ySn3j17PrnldG9Sl31AHq9Xt1B43V9+rS2dO+lzqkiPG0G564dKWne9Aa0ybiEhVz6N1uBe2rDJq804X4XAKYPdB9EbRUnKefUt4DbmL0HfzdH+dMbJjGbPTZC2GNp+39Evdbqx4rsCl16EX9MGelmfi7Nk5OKG3DGKzVwTmIDOb+0nUEWeU/dlq/UrblDpKuYYO2V7TxkeJFftHnB71Da1sVfp4j8Wk7z9RKQVNfe9fy6V+ajpfXxkJ56d9zYwJA9lBCHwWQG/NPwo2ixbKM2LSYSV1ySk/wNghdFqHDBwZza0MTNa6+huh+lBNzQXVpX8semxy+jmu1u8bq2V13+TOaFA+AO5PlL2k0Gh9+ZLndYaFZpkEYxCskRAKFjH52M+dbmVwGQKuD2S3emM8Key3o9/hplwZEhjNYGM8I/kCd5pBFPQiopniGS0i4Wekp6PtABvFsh1Z5a/8eLgLOfUHkdwVZ343Sk+njtglaewTXW45wc+8zdhhoLtR8zc+w5Lk9bOL1DP7PH9wLcrUGkvXVMGRKkYwqyK+nhHtZPUXV7P6LFBF9kAdST83v7nXw+nLMMK8wSY/iA56aoGP1L+M21lcLW2ncq5kp5Wy0y9+2/RknTdutpfTOXwC8Dzd0IIPyBPUKIQQjiJH+TD1jS2siBGyfjwCd49N4qEdCsKlJhcOnQQwepSwv8uxSwaE64qBKn6mYNJmkD991ZbC7YoiOYMmu8fVipQYSOmyc2nCh6T/m8UsQLtH3t7g0Fd9KIg6Ijlwk5ASkKnu57sevjCf5qYEUF02yDj2iM6MMfXNW04GYKpaxUZrxGsGIBKVBtMfupeuEbxXooZJ434kmhfZ1m1tTxN9OeSISt4VLgdjUJeNbLMqCPfjev+L5JTFjNql0n498ncTJUruiEEGAgSiaK8ZSaV95FT95dCDyCJ0vUI5NUhrEXrKtVvTXN6PeGHENRaBoxg8N2FHIlMTluGM+9kN6WPFQ1U337F0RDG8cLkUiHqlMjR7tDzDadLhfpuWnN6t7F3QV5xRnE/Ja6ANnFednnWAU9I2AHZk4FNL6Y6A9c8Frj5yFwKH3qUW9ckLI1u0tEJ0Xj7KUnIyl13IHo17svedj44lXbp6TDKZNvF2pj2iOPvSJ1gt6p4a/7Jj5AFDp+ava6Pyhtzr6dYdGtF9tY+gFUrUF0UkPKssjghzA7DEHM4IB3GsJvSQ+Uq8k77l90PBzwxOGkztQkYrYX9xj1Nw6TPQ3kuO1RrsZvzcsjgLE1Iwy8BC5togwDKAGSXddA0V3ZvdfjA2FhEt3Xn1jZcFV2Peb4oCfygjD0qX7DBVgL1vo3hQPx0NrGfHhNt5Vnj1dxvHXA/RmK8icTtc5BnAlckmVqDUbn6iNs427Pt+dAVVyIcpbCaBjHrZ8oqyE6L9kNwymCbDYh9bqf33R5+gNk5FXRXkLoKfQH3hlHpdeoG4hQ4i7BdCBg4IMQfr1IUHRTID3lUgPdVq0go9KfKb3YtZ1nLq7GlbBgyMDLEMBiwYZVsmrGl45shHly6GMnyeCh+Z2EmdHU+nC3cGX8dwm841UzXRM4+pC/2xNcE4vZpsNiFcq3qJNVPTdHPgzpd/jlmSDxLlLGDM/TS9+22d3QYUMBH1PDC9fbXcexSWM+XF1qMrfoaeoOfH61/Biavs2EKMYeHGsYfRrlToCtvzda2DcEYyd1A963Z/TxSfFDVEygo0lXdWI7cdEA4gwTpRz+PM3V0LE6/IhJINEbtfLLeTBrKyXuOEXOSu
*/