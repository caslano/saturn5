/*
 *                 Copyright Lingxi Li 2015.
 *              Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   text_ipc_message_queue_backend.hpp
 * \author Lingxi Li
 * \author Andrey Semashev
 * \date   14.10.2015
 *
 * The header contains implementation of a text interprocess message queue sink
 * backend along with implementation of a supporting interprocess message queue.
 */

#ifndef BOOST_LOG_SINKS_TEXT_IPC_MESSAGE_QUEUE_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_TEXT_IPC_MESSAGE_QUEUE_BACKEND_HPP_INCLUDED_

#include <limits>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/move/core.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_1(n, data)\
    template< typename T0 >\
    explicit text_ipc_message_queue_backend(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        m_queue(arg0) {}

#define BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_N(n, data)\
    template< BOOST_PP_ENUM_PARAMS(n, typename T) >\
    explicit text_ipc_message_queue_backend(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& arg)) :\
        m_queue(BOOST_PP_ENUM_PARAMS(n, arg)) {}

#define BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL(z, n, data)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_1, BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_N)(n, data)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief An implementation of a text interprocess message queue sink backend and
 *        a supporting interprocess message queue.
 *
 * The sink backend sends formatted log messages to an interprocess message queue
 * which can be extracted by a viewer process. Methods of this class are not
 * thread-safe, unless otherwise specified.
 */
template< typename QueueT >
class text_ipc_message_queue_backend :
    public basic_formatted_sink_backend< char, concurrent_feeding >
{
    //! Base type
    typedef basic_formatted_sink_backend< char, concurrent_feeding > base_type;

public:
    //! Character type
    typedef base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef base_type::string_type string_type;
    //! Interprocess message queue type
    typedef QueueT queue_type;

private:
    //! Interprocess queue
    queue_type m_queue;

public:
    /*!
     * Default constructor. The method constructs the backend using the default-constructed
     * interprocess message queue. The queue may need additional setup in order to be able
     * to send messages.
     */
    text_ipc_message_queue_backend() BOOST_NOEXCEPT
    {
    }

    /*!
     * Initializing constructor. The method constructs the backend using the provided
     * interprocess message queue. The constructor moves from the provided queue.
     */
    explicit text_ipc_message_queue_backend(BOOST_RV_REF(queue_type) queue) BOOST_NOEXCEPT :
        m_queue(static_cast< BOOST_RV_REF(queue_type) >(queue))
    {
    }

    /*!
     * Constructor that passes arbitrary named parameters to the interprocess queue constructor.
     * Refer to the queue documentation for the list of supported parameters.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL, ~)
#else
    template< typename... Args >
    explicit text_ipc_message_queue_backend(Args&&... args);
#endif

    /*!
     * The method returns a reference to the managed \c queue_type object.
     *
     * \return A reference to the managed \c queue_type object.
     */
    queue_type& message_queue() BOOST_NOEXCEPT { return m_queue; }

    /*!
     * The method returns a constant reference to the managed \c queue_type object.
     *
     * \return A constant reference to the managed \c queue_type object.
     */
    queue_type const& message_queue() const BOOST_NOEXCEPT { return m_queue; }

    /*!
     * Tests whether the object is associated with any message queue. Only when the backend has
     * an associated message queue, will any message be sent.
     *
     * \return \c true if the object is associated with a message queue, and \c false otherwise.
     */
    bool is_open() const BOOST_NOEXCEPT { return m_queue.is_open(); }

    /*!
     * The method writes the message to the backend. Concurrent calls to this method
     * are allowed. Therefore, the backend may be used with unlocked frontend. <tt>stop_local()</tt>
     * can be used to have a blocked <tt>consume()</tt> call return and prevent future
     * calls to <tt>consume()</tt> from blocking.
     */
    void consume(record_view const&, string_type const& formatted_message)
    {
        if (m_queue.is_open())
        {
            typedef typename queue_type::size_type size_type;
            const string_type::size_type size = formatted_message.size();
            if (BOOST_UNLIKELY(size > static_cast< string_type::size_type >((std::numeric_limits< size_type >::max)())))
                BOOST_LOG_THROW_DESCR(limitation_error, "Message too long to send to an interprocess queue");
            m_queue.send(formatted_message.data(), static_cast< size_type >(size));
        }
    }
};

#undef BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_1
#undef BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_N
#undef BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_TEXT_IPC_MESSAGE_QUEUE_BACKEND_HPP_INCLUDED_

/* text_ipc_message_queue_backend.hpp
giORHU8U29U3KGG3/hpndTesErc8PmB5eZH4sallhjwuxqhiuBCDqFJchTgj5qUg66bKmHn2sPI0KpO8JbIkxtiRoCG7sqN5YHp9HCGD6qYoO7gKv++DoIlkF6OpqaAorvXopY71afqwr8Td1UD0r2Cb1rrOEX1g54GwdwsCnLP7fJ53zfqwFvL3/Egz5wSmeQ/E60ghmnxa5/qheigePKmLZpKnxEBlCaji0+bwowAb+VRK1jyQ6HjeeGssp1RKLCT8FXk4ilhh6WkScyfNckvUppSHOJk8tdPeW3MfpbopqZzNe4yFp4fFziiSC0TdBdET2g3hLI9IkyOiIOaMoExAmnG3bOhgHmRElbImZFYtbOWr84kE4XzvV2Uj+gGCdmRKVaN84mV/qGoPy25DzwSk7u0OHL5/44ilVdrWHO7Q6t7JCZVivNQQcoZqhvHEOqV+LJRiC0lAa0ZEo8s/HcBHclpkswJJJjuqh0kNocH0gRlTtMUybdZcEdGkrmmWU60s10pbTXsNBX+X6RANz5kwryvRUp5G8A6YU8W5wJ9Zdg0rR9gTxqje9rTHT6s57L3evtrvNbr3GrGsgjSua/G92pdZ6Lu4o1QIkhGOcVXxxHQTCX14B/+CcZXHJ/InrSv6q3hbH/b133RpZhkx+i7lhqyaAG+STEX7HIRSiVh3DcZ/diRwJ61cDy/E2NatauGeoDStgv+yD7pA61W0u9jOBU245+ZNdULZhKydJjGftpkJQtFDy+eJF+QrKqpsPZfdk/w/qyOuqiFgHpBvZFJKihW6fbg/fdhCoCNDy76oY300afZ7y8w6klt4h8nxEpxTB1GsSGeu94hmKxhWu1XdZPfxlYQl09Q7geHXuyWHBhgDPYaWT/4q0iKwTGCuBQI32/gKv8UvkYp6+Bhp8E7+nL5i8LCyb14decKomhdMyfrbMs6AV7mBrCQzGdjEGTqkZJsh0adzhPK8SrHs+o7vpJizwUZ9zcYyUTnDtHC7Dq+FYkJ2DbFcAFK+hGvE9fxT/1iggVuwM3ubx3SPBJ3sdMlj9IqpLrxCYoamSM2yWmhKmk9PNawTRcXVQ3MQ9TWbCasHfdLWz4UMZUbIKN5gpR6Oh7uy/9agWz2ltk3HSiPS2ttwGhfR+dvYGAtQhM46jBT8iO9tXqGJlKDvSgjSb355rZKjTScRBL1KCHq5KDJ3z0gS7vW8ETuH0VyCZQmiNFex4aOysBOjy1FGpHi2LCkqAmPYEbM1M/YwC8y8SBHcKleC4aEeFeHGjlEaPDPMEAmnek7xYJcZOCmhwc86IxOxZlAdsOZuuwQ38o+L2a3ky5uHLSta091oAnjPbnvVOG42LXJfWQvi9bFoO7CtV+8pmzj1D66fm0ArwD4X0yQY1vG5eunP3jKpeTElcLWYAJce5N1O8doDQbu/UXfn2nqtIfj0E4M1JFhrijuMyEOw+3g6W6Sx+wMI8+t0z/B/AyS4AUgiB7TfVUhXCKBrv6ymC530xqTVEXrdMf8kTXcv353BjOKyIATFKIgb+luvl6B+SZ3uBNXCThPDAKMbbxFtpebq2l6PsyKXvY7X6q2s20I12kDbhUNik8PgvJiuX8D5HCbOteu4+LO2gCfOqudXggbwktcUT8BbLxPWYCx+OmtG+G+rZ0l+zczwEBAv0uqJLC9ELlMOOV6BAuLlmZtAn6+tJhPUodREErW81675u+Wp0MEHbJlWgh790lWVN7dUh/qCAb2RU26NlTlCJKQL1r8+d2ugfno4JxXuqBSyAmu4xm5GVxcKPnASMhg7Iqb79/sDvzv0w/WrwQjIPLLAWYGKvwoykH0new9Bn8IRIL169eDHzfVbEQBnAUIclsTVhSgbNyqR86OD+TrOV+GfLH/DX0Aho51m3Fyvu27WCWqft/VnHtw+sqsCdVB+L0dAo8ofrCdCS6HmbbNVETE8278wfZbHpwNYb7bL9q4fGHnmKjQfM8vBA74WPx9sRjs4AEE16BR6Nis7JdfQqWvmdbmQy7Ms4nzu4dt3tyBXc4u0P/umVouSrwz2C3aJR8KO05n/6VhG/lKwat3PfmTzrAMG8N+ILn8MHk5AqERm16Kz9tnhaCwRzKN0oQZXrM5TBoPlU8/b9CriuhEAbWOwn69QgYxbXDxj10i2P7wgv9zvz1RZBWxZGx2VkeTYD5JrOXO7EEVz0/rscLT9NPE0tOYjE6LrDT3q2mcX1SJ17+/BIxVYNcMnZ3k/qJAFjTczb9/B1D+HNeRcyHIZcqUnwiQe5Lx4DnjPhN3IBvr6tPXIRzNuuSSdrV5tx90snBLdH5qOR3gdSrEhgprEIlkh5VN+QG6cC5ZF70S76X+2IYVDSZBEeXpYcIffnhmTwpywiGYUV4efj1poGWq5MJLSNV14d64Ua2nFwexVLNVm3WTnWiyXsEzfP1h3WIKs0YRl/WCI6O0uNbw6h3gh2LpGi9Nh0pL4ikiLB0+Y+orEzPaHasRc7Um5Y+YXz2TJVpk5VNtPlNTr90Mb01HcEqNkkLCnoO/B2wSTaOF+ojCzCgB7Xd/LkXUmimJ9xV/zpmKNjDPHJS6JM9Q+VGQrJoRdtM1NijoZJ8uz0Tijo4FBXDrneC+t0bH0lpv9fHH24krJHu8/NPqjjrENI/NWDTdz+KGtUnYzre673P9oQZHEocO3/Ds+F8gfCvnMRPrkJTUYqr5pw7C4rfMO42RDW4UcDX92sxEIazw5geUDrdcQyqp7H7so0qiWpR6aqI4MvJ8p0VNtdq5mt6eHt58uRnHYVHGfnEAm3fFUM/Ti3NUl7GpKjIszwYeO0M05v7AtF3Ctd0WpBn1E1na2KMXOOu1dw+H7fiVUmH8clX1NRbASaZWzTwUmkwmEU+hKiBCWcSt3BobRWhznYNFxjeSMYCAaM0TyAerNu0PG0xkX57935Sr3oYK+TNMkTHpeK3nr6N6SWVAo9X/vsMVY3vvuL1RliA1fXDgQy0SD25Gnjx9/xwiyg8zkw6+nsV6QhNscGNo1EevhqBWM0Q6mCU4B3VOuISgkWnKjJMT9mFi9jYRuq/lkYGma6Ubs0AEpQWI0595u7bfdksFi43MS/+VvlrvcjgBj6IpR7nq1UGWPiTspcQNz8IyxKCCXId1PKrZR1zFiWGz28hWL27RsistSCsC/NCdNGPuQEQEDS63qd0B4GT7UISaU4c4lGVQ0zBO5U3Qi9NHA3kdqzaL0ZM2yGXxe34KrMNppyqO1vz2fjk62pyIsL2j573zjsm9F8IarOKNFrHh4GBbSxNq48N9pdwQtxMMLqh/u7GilUtJg1K+kR2NwLC58TFPAqt9n7JbrwqcF8DqLoeuZIEKMS6xxtk3A0NrAuCYYigBkcyudsKOaU7rC+kHeRKji2CC6IbKzu0oWvm3biQp3tstOgos4gaJrWLvrcBi6/6QgXctRGHl+MI44ikm7muN6W6yuEXEbEmk/vWUcMo0agasA49mO1QAnZ3NEax4sZfspgZPWErohHe8d/fPGDSX4qj4dPLRVWXA0yudxd5QLs7ZO97nIJ8XeVP5gYbEs++F/P4Qne55ZeDnZlrta5VDLccb79kb4Vbp+4a7NwPibLU6Kis9nXJH4NeUJru1WOSZ+h8t9CvZh2qwgEenjQyIz5YYAvsgHpM5CK1RxyinFlYecl9hGL/eqYruAyLjv3yHdI/MjrGZsrLomS0Gs4VgeBwfKfAf5D7YqJsjBzlvAktYIHaLjIs7OTj4qLz4XZ6oO/m0ZlcU8cQUCKiEeV8Sg2M37Xlavr4eQ6vuK7wtZyF0uIA7q+yu4GhK0I35TqgnABmySkewvitT7NizG3A2jIazPsmn1e+DCQqZbHYvPB6gurmw+XdfHRC4YnzfX5By1g8LC+v4VAfIB+ChIiEGtuIpexGWjWAwCI3MmrzGYOZ5E65FaIXL9LTL0h+GVq4ZtqjajZpEcGyAfLZDexiRND21N6uFJrKOwpa401mAEiEe8T9KhZdq11farbrRUqm+bIqCgxTEf+S+SIFWRDjaIKtZoGhNjwUb6Atj9JSlpqjVCE5A5OZc7vSfUrK7jwSldn6UeT3C0prjTPBCg8UH/dZ7glhlq5zEgdYysOY0rSksOwbnW3AMJRx+Val2ds3OZeYhkH3Cy2dPZJRTtmkBEDB4+GIBn7LxeZI6xJf3dVPkcq38UdfnRyU4muKga6e2h9DKbQ4IoylIk3WlNgUICd5avVMsD4c3mP/DZyjwVpY4F01LuoY9a+SzT4kkHz6w8Egd3D4NzE7GI6heI4ccb55viI/VaOwwHWIidyT3yboIiDVUD/nswNMK9ia+wnZWXnRNdKdxQNdMK0Te13iqtBjSn9Sr+OgxQjTAmsYzFXAQs9zGC55SgbKpYgrQqzNJ+22o6bf7w3INxYfeV6EyVEqLWnucZWci8lzSjJFXgKWiwZikjM0fSjBKqZGaXKG4W+UjMUuGVL5//FpI0ZFimFn6WOja4FR+nklJU95ub96CVLbtZB+OqZG4NV1UqgFUTyh0gCFA8Ii5R4QidZZt3PBNHI4qzGkMduHF+7+ASqsTsa3jKqL57J5Y54JF2ZENo5+tW17YopjNCOP4DRMMNBzf6zv40RXtGHufFY1OXh0Ha4zMj9TAmlrGwbEVnSsAcOE0IxWGSv5BjSSJXDqzB9K5ZIst5Ys6O0vcbZKi9C759uU9po7o4du4wXVXe7cl2a/cLVTxqgk8jw6i+ho+sbGHOV2lxYGN/TfbXzZwsJgOqA8Phkf6R4nSv2hlMFklnH3S53LWCIJkMnnq95qadPsclmMvLK6VHnKTsJaJZ7c0il98/N2hYTbCvZk5R+DLeAbarUh9xHzkiqmrdzwlr1r452w+EymELpK7WSYVBrbE5hPeBGf9e/pTXrj4sDmydPBATcf2kIpFmGz0M8ACw7r3KZCdFSm4NHnhcwNhFGklLaLm/PoIYrFqAxNSa2Wfslh/YjMtWfh6LxaKRUPGLAnrjnViirSQOFuIUkX4jHlNoriLNsWelOkYFkeWcl72gqb4qUMTDp08udJmiSQuag2tiWhwByMmu2Ct/3XggTh5vEyp53+lNPta4z3irDiYFAnb1WgMzIW6Py46rR/Yj4ILAIob5gP0HCK1U6SwjOuH4FgYQ2u2WN3iz7Eqk7E2zYG9Vstmq4lymHU0iiwy284obA/7DFDFoFbSpX7Bk1xYWjfr8b6lE0iGpSxXzP321U4w242vuhNefmiKy0toDMmRkngx9xohO3PXR7T79qBnRc9WH83wF4R4XZlLu+K0Wd8KXGJ6BbVRb1jqHeqlVQd0KmqHU5IEtV7aNWHa5LUvhfxitQZ4ONhlsO0ykfQqhGxIW4V8sTPoCOvLWNyaXLStLOouCLFkkbu6Nqp+FF168uepyoUWqDZ/HCzvkksXxTRDHN+0JQsbOq+tuO1OjnwmVZTUHozA4AfNNl2drixflL73BegGWApCgtwUgVdTv3voX+Y3VRWXqiloBVe5lAVqXXj9eUXGbY354zatXelBtA7s9ZW9tBu9A4Z3AuclLSOICzTfqiCs8VobARmtyStFQlIv6ESb95RIojEHcB4FY/0KjLdxTG9gXItxTWygzp554fzeQgGxhA95mMxbqqewkEFI8brjoFnscwhuohTrLHuJSrKiHKB+UU3VOsHcwrdzs6g02R5fOq413o9VFAm2zAwTcKG2PuKpV9McVO/aNJPEQaUY6Cy86Djbb7I++4jx+NC9WPrYhrm+js0QvoA6l3gnFPWxrlU5hGCBQi9pcDUgdpVE+2Rgrp4cZygV4rqRitVNRo+weF1LSehzbv2xcngTGKQ/sAZ4HEjUVZWYWx4SiQHPBygLUfElKYPmqlhS1G5wYtTmazktcOdwZvOfAZ8QBJmxmCZsGSEdg55uorDCcVz5Gqf7djWgLJmCp6Ezeaz0DUQL5STxnK2Wn2FzBwToCHHJyFCYgNtu1KTWENjUJuGFiM82IO2PJbPfeEkCyZHd7c5SgzHwsziR1SQge9N7xtoTk31RfYIElX5+4P28vRqykMdEToh9tfKozuGKmBDg5CWMzR3+VQELGrDsQP7KMxhMUH++rc3seoz14nVwwp8oNmW1WVl0j7b9AdXjakdtepShlzZNeTS/zOt3ORd8YS+g6FIjAgq4CBzWMXmhEskfQQCi6ETZts8wfcVcJpBi8o7VgK8VqDBK7vNuI2k/iNGuKtLhBVjrSy15t0173s/ygDnKUEkvUZL1ewepeyrB8O8DeLf3sMKVoM/L5Byg723gleYQvDUJQRpubXHdoxIXipTeKYX08kbW5f1MU2nY8ZT38ADqliFFJClE14fkoh6vVckocxTgOy6gt7MgLy/1rddz+xNmc/hTXJKOT1GjyTTz8zvQ+mw7LelyQaDz3ViReoTfT0IjXSoJfYX7aOZ1P+08qbEH7d7RCDU9oIXwh1O1a/cgQ81+0cEDlQhNlNbIBlQh5KxJJaWaWKTsLZEv11H9Fu9tnh8z3q1hafvuC26tvhdEXrWSVURnIyBZL+wqQus+H6Yl7CKo3wTwEBCdJIoGSA+Skyg19ZLddQU/iIyy+QCMkZCzJmBeiw/ZpsYVGIqZaVct9evd3I6mvBQPh59MBFCPonbo+id1BtindDpKkNqPXnXUZWEzcdj4cC2QW3O04ldJqO1tTKK3WXY6brDebL91cx5baJmYqQ63eKnYpx2pnC/TrsFnEJl271EFW77CaypzrPZQ/x5lbAFoWswdI2DmN81rEWckd5BT8Dua4/9ARR9G/HR5GJ60bozUO7Q5VC8IxokFf4JhLR/MPaGw3fyexcG3E+cv/Q6OQaHTWZVW904S8pesoOXb61HQ4xJXSHRniVt+ZZr3vDwvu13BNKw7CJ5563qykXQWVTUBJ6XNCwKdyXGwK//dVrwmoA6Zc2nlXw3hu3SPNeaAZIKsLsAoxYE8eyWqX+ai1q0WxtTPVZVu2MbKsmSaQIY3ScTePIzFd6cUc07IO7FlcOPxhVkuGG8wDlnv2zjPbRa7iTA39GKH6yd1PhrwdAuOKG8TJSqhq4/yNibaRr7jD5iXDqCsZ0MYlP5NJuG79jAx00pkCbJrBdck6UzAWGNeWP/D96FMczqF0enhtIYBTP7+a9oNmrgbJlLi6zG0IjytVRTxpXFsi0BXr1bd7i+sy0f2qsLHKdn/PQuhHuyJMShNI7xh9x91llzOyu+f0+AI2de73mXGBkJN4BjxOHoFQ3JL9LW+/ExXmokfQklnk1jUSDZ/LnFDMrPAXyw/wCemJ5qn+xf9m5uJnI5ZGhcU26EEvJpGw6lPiQTNVKcgMAo5fDLXC9XWWFKL1v5We3mcG40yljg35q2HW9XIeJN4HS721bHGs4E6H8mwwOyZZ5Rx7dysMJCMukVkQnbSBAeEIdXEjBTNrZUdBL8ge6qI3XK67ve0aVqxWobP4MnNuDylhimd4uuz4Mbq3eJ5UG0xUIa6NTQVbzwQjtzfjNCLsNnx6eJPzkOmTw2W6tyrdF1sKUfsvM74ff36W2U+nr4DMGYQNGv0r4Njw2YRdoLZokWx4enH/C0tM3d83tFspGOywIkLQN1C68AYud1jGYRjErjsfFUZZyJK31Q14T7kb8ZWrK9GpAvudb2XrPAoXA0u2opCuQGBqYcqOHnQ0FGTu/7UwLyfaTmHwAV0iC+8BxlFfKf3H3ukG+6ATxBA9xH8pHiJwhqqcvaqLUCpLVHy8DKuqSODWsd92b6IoF8TQ8NRZPrDNj50KSZS42YSCd9bkjPz49Z3iA1Pen6pcXNU0oU+tZPqL5VhJKXB4DOkY0z4qO8gLM5QbmhTxGNAKI4IKEfoBT8DbJUDxTXFdft5S2VgP6ALvJhonflo0pqhlnbzqYox5LruOS/myIEaKbsoUi1h3yqcy/nkpRGvlm1/nDGG81pkSGNG6OR2A+JqPgXuNirkToKpm1vMIkjR4dEJM4iV+Xy7ZDavA4bjOpcYpu+TiBl2dqmX0JRBww7l2vpOf9P6rNTHCRv0lQU1rLd4TK+qGCcG+kAxck6Fp8tNQNmwoJmxeJbtNuhHasLdua9TSYfr9pEtn4DVQ4XqjhRU1CE/ooYT7nVei/EqLzuCSta1TanHNGqUwZkGsvAFS5AJF9b3kCsdTapLQwl5cRXDb3RNcsqsn8xlusqcla6ON/dFy8fM1KGr7S6KDRrmOUW2lUTzKTN4J59tkDvAMlguZoNhdQyC3CwX5M4PtrReioh03ac5MtmBymw/8YVzoCSiQh4P9uaNbvIwHyFPyZesdoPfsuq2lq7DpGCFkYRQNj726lfAGMcV6mJA0/cxZfp0wLJ0Aa8iHy9Ej3SckuIvOcr7oeJ+k856N3MnQupbbpe+gvQ/r/8FIVroRqHPW1Uy6btAvTonRvVEeRJFpiXu0uY7wHBmnqdbe/uPelyVkftljrHpf6lFUumNkH/KPtqTi37OHNszBpqiCTt/mSdrL2/sGqIShdV3XZ4XOkpZcPgCyamQg0/6FdTnoGKhTeXqdEszZSJdUFEsHd0KA/tLOxzC7kt/pisl3r5yivIOH/a1ZC8dOGQyzoWQKhdkAsuhDQZc4Bi3u67Hef++eEItBbhByK3IjtxwLyF5k5gu0xbCG48bnpli2h54r8UfFFJ31cToLPTKqFQHR9xqLm43fph3cLlXMaXcUUaKPWizKPSxe7NneUOyc+ZKPBZYVADxTQaM1zAZ4RlOtrDEmqItJ9Rah9B0lIv4BZyQ7QUktP+6XFtIU5jhcbouXLsu4PVyrTSaMcdGizesXrMJiMmLxnC2IRDMypStSuf82BgPOYdbRW3XWgjPPh5OmVEtAM+agqZz+M8y80jEJpwM5JhwxdOrVIolJuzR8oB5094CK9S1GofoRIQdzkKNbU4tScg8v2ky7NpzzcuS0Bi4SOsbMfwvo6cJ1q63CGXOfLqmL0SISq8E3ejxTOM/2aLfJCV/fIXdsdW4+TvzhTQk6nZ7P8brL2gy9r3RxldVgsclovvPZlyx6UPo2nESZkdwb4L4oG8KQjxXBt+6NYsQugCmlp0E10AjpBm9b7iGnvHixC8wMkVWBbxWGF0nls95Ar5BgtNp0oRIMz+VmHf0uehld4XUeT1LjiogtjTc+ywByEa3DKmr7WEOWwbU=
*/