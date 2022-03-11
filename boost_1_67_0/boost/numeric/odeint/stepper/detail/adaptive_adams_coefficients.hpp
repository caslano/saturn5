/*
 boost/numeric/odeint/stepper/detail/adaptive_adams_coefficients.hpp

 [begin_description]
 Calculation of the coefficients for the adaptive adams stepper.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAPTIVE_ADAMS_COEFFICIENTS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAPTIVE_ADAMS_COEFFICIENTS_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/detail/rotating_buffer.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template<
size_t Steps,
class Deriv,
class Value = double,
class Time = double,
class Algebra = typename algebra_dispatcher< Deriv >::algebra_type,
class Operations = typename operations_dispatcher< Deriv >::operations_type,
class Resizer = initially_resizer
>
class adaptive_adams_coefficients
{
public:
    static const size_t steps = Steps;

    typedef unsigned short order_type;
    static const order_type order_value = steps;

    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;

    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef rotating_buffer< time_type , steps+1 > time_storage_type;

    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;

    typedef adaptive_adams_coefficients< Steps , Deriv , Value , Time , Algebra , Operations , Resizer > aac_type;

    adaptive_adams_coefficients( const algebra_type &algebra = algebra_type())
    :m_eo(1), m_steps_init(1), beta(), phi(), m_ns(0), m_time_storage(),
    m_algebra(algebra),
    m_phi_resizer()
    {
        for (size_t i=0; i<order_value+2; ++i)
        {
            c[i] = 1.0/(i+1);
            c[c_size+i] = 1.0/((i+1)*(i+2));
        }

        g[0] = c[0];
        g[1] = c[c_size];

        beta[0][0] = 1;
        beta[1][0] = 1;

        gs[0] = 1.0;
        gs[1] = -1.0/2;
        gs[2] = -1.0/12;
        gs[3] = -1.0/24;
        gs[4] = -19.0/720;
        gs[5] = -3.0/160;
        gs[6] = -863.0/60480;
        gs[7] = -275.0/24192;
        gs[8] = -33953.0/3628800;
        gs[9] = 35.0/4436;
        gs[10] =  40.0/5891;
        gs[11] = 37.0/6250;
        gs[12] = 25.0/4771;
        gs[13] = 40.0/8547;
    };

    void predict(time_type t, time_type dt)
    {
        using std::abs;

        m_time_storage[0] = t;

        if (abs(m_time_storage[0] - m_time_storage[1] - dt) > 1e-16 || m_eo >= m_ns)
        {
            m_ns = 0;
        }
        else if (m_ns < order_value + 2)
        {
            m_ns++;
        }

        for(size_t i=1+m_ns; i<m_eo+1 && i<m_steps_init; ++i)
        {
            time_type diff = m_time_storage[0] - m_time_storage[i];
            beta[0][i] = beta[0][i-1]*(m_time_storage[0] + dt - m_time_storage[i-1])/diff;
        }

        for(size_t i=2+m_ns; i<m_eo+2 && i<m_steps_init+1; ++i)
        {
            time_type diff = m_time_storage[0] + dt - m_time_storage[i-1];
            for(size_t j=0; j<m_eo+1-i+1; ++j)
            {
                c[c_size*i+j] = c[c_size*(i-1)+j] - c[c_size*(i-1)+j+1]*dt/diff;
            }

            g[i] = c[c_size*i];
        }
    };

    void do_step(const deriv_type &dxdt, const int o = 0)
    {
        m_phi_resizer.adjust_size( dxdt , detail::bind( &aac_type::template resize_phi_impl< deriv_type > , detail::ref( *this ) , detail::_1 ) );

        phi[o][0].m_v = dxdt;

        for(size_t i=1; i<m_eo+3 && i<m_steps_init+2 && i<order_value+2; ++i)
        {
            if (o == 0)
            {
                this->m_algebra.for_each3(phi[o][i].m_v, phi[o][i-1].m_v, phi[o+1][i-1].m_v,
                    typename Operations::template scale_sum2<value_type, value_type>(1.0, -beta[o][i-1]));
            }
            else
            {
                this->m_algebra.for_each2(phi[o][i].m_v, phi[o][i-1].m_v,
                    typename Operations::template scale_sum1<value_type>(1.0));
            }
        }
    };

    void confirm()
    {
        beta.rotate();
        phi.rotate();
        m_time_storage.rotate();

        if(m_steps_init < order_value+1)
        {
            ++m_steps_init;
        }
    };

    void reset() { m_eo = 1; m_steps_init = 1; };

    size_t m_eo;
    size_t m_steps_init;

    rotating_buffer<boost::array<value_type, order_value+1>, 2> beta; // beta[0] = beta(n)
    rotating_buffer<boost::array<wrapped_deriv_type, order_value+2>, 3> phi; // phi[0] = phi(n+1)
    boost::array<value_type, order_value + 2> g;
    boost::array<value_type, 14> gs;

private:
    template< class StateType >
    bool resize_phi_impl( const StateType &x )
    {
        bool resized( false );

        for(size_t i=0; i<(order_value + 2); ++i)
        {
            resized |= adjust_size_by_resizeability( phi[0][i], x, typename is_resizeable<deriv_type>::type() );
            resized |= adjust_size_by_resizeability( phi[1][i], x, typename is_resizeable<deriv_type>::type() );
            resized |= adjust_size_by_resizeability( phi[2][i], x, typename is_resizeable<deriv_type>::type() );
        }
        return resized;
    };

    size_t m_ns;

    time_storage_type m_time_storage;
    static const size_t c_size = order_value + 2;
    boost::array<value_type, c_size*c_size> c;

    algebra_type m_algebra;

    resizer_type m_phi_resizer;
};

} // detail
} // odeint
} // numeric
} // boost

#endif
/* adaptive_adams_coefficients.hpp
C1XUpjIKgv+ewALnMHigicBI8JED9Ehgksc13dkncFsR2kFdpc04M5IJvlqSTJHo48SszsslatHr09AZqh5zFmQimebhzVXSG3kYZckkQLOjHkxviSN4yFbxKEKKdIU1FKNXRlId4145Al7pzS9NctuW1XEHIdIIdcTzdxgdoZ0ccUL3GLL88841HQKBtYkdFNvEF9rGXSZDrsGoYaCYibvxyfFOBVF8rGchsAtIoSTBAY26tdLfdbS87RB9P1+aYSprNYJk7wjIINkRAYro3NeyL1SLQbL7kKaVUL9Xl2awuntNna6rfZcszYgLl0ylQnj3lcOGo2J7eormhY1F8AE5WRY7opy/moYUJ1ropWq2Pz1sJVT5t03SD/0qSl4eTnUdBt5x8JJomkVQbzZUYcxTf5nlfDplOKSyqVi2+hKZftAvc/1gzGcWOwE8j8GedXWharnLDhxCDMdtce3pGdhbtnlTdaSLRGPZRX8l14ajROajUAbj0l8u0vUmP5xrN4/D/EWHFPFuVZoExh9qbteER5uhWhddwoHyhsxaJGZYIwXcBlu5g54x2uHDB45mczt6FVOkegPB5siG2Cq+knDRG+MaA3MCCm4gINST0xPESV/FAYQdSFTG7YmifzQh/mbID8yLuDNuHoVTDzTCB22LE00ihBJ2dBVFhHhhlMJl8SFgeJV+0cU/rs4QTRbMg7fKdfVJCyKOHyVz83X/613n47tIjyBWaVqk6/I1PniNvrnpLSAe7fBdxApCmLevyOVLD3SNtTjyiCSGIhG0Ii2Mw0j3kZIwBsc69PefoX0rL2YiErfacWzCqV/j1QV4teJQgBJcbfATcgTU5+MY0bwaCWuTsBbaPfhf0OdxYSfHW1jYZyawNGSPyzLbBicIZaKShPYxrWi/E5ay7tFZ4SbjHhB4WWN3mYFjEL4yVOoG8ruWTPn90QI7vZ8u8Id/XKi/EX8qKLl679JEGAAqNGNfaAX9yNUVFxGF7Sl0AGAo/Jen09ZLqBRTdGDQiuYFOTE3mn/AVl5jisad35yuhKrTyXHdU2WSOR/dYohTW1jRqnsoF5ov7GmR6iMQl3ZkTit5UpMEQN5HXEMvpxKi1Xsk9+954UFmZVy9PzxkLKW2KYIlNK5JnwYTTbpsJ8oNqF/Wo3450K7XV1TP6gT6JTkQWPU6AmAkJOAZ9qazoKPXWdym2VrqmuNIQ09yD8OIfWRiUQwHJQaV8l2cvcpTxfh2ez3lDYGzQbukIRG7tT9+TiQXkH4wjrG8ZWfGWe+bPjWDMbUYIHQ3moPDqRmf9+IMsmlZ8axNcWtr9rL9eLsi/sMYpAeQmt9XRAseHyG0OwyQPRIYihlWgt7QzK4mTE47hPSGmf3XX4Dj+S80bMB7+inZN+QonxytqC7NQJxdJXzrWAOW+vdpaSaJAA+85AUfonuVkB2jGBSAC6angf6IXG7ynTQJzwTqHrffgcYBN69EHArz7Q4DlD1YorgKrcE+YpjdG3abac96Idq3H7eaYM238jeIOg8e0hFmXYEHcUPPoxbCVCm0KqJrQ5F6ox1/+9U+DUVhvBYfqxk6qFDTvBTNJeqRZFFiM1IDET0CDYOqYMuCnxM4lTMSqHbhz2RsV2QOrjiPv3qYv3ZOv9XYZvrCOMMU3tjNMLejjAzrqOs5mm7lb6FYTbb3VyxxtncSp7wiglm3FHX0fviTcJK4L1b1GMLGaWg/4izXq7R7hjKo1CrM+INYYKtcL7ZBqEMssKpJMSywrpMxR8EwXnFU32xRa0hK0NHLRiEX8x3APFT4wkTh26+jfbAE5ByOoToj/JzXOQWGOgBtJAOS60WCfit/I85GZUTHLSbAw789gpZWQfcZia6sBue95vjmFNTuRd4jX4pmRU9oBW2NY52sovhgdvGBSJLwOwN4IRlzF0WSoWOyffsxjRYM8KgYuJ3XMEyN9Id9qzAlCaU6z8PQUVgPCKFOXYKvz90XsRC6CTRgPPzd4hf/xmlGCY1+TSC/6cpi8QOdY1uKxVUx6LuP4QIw8ckct5bkjH53ivxuA6VHgU+nYw+VIsKdywuSqQPqPx0dVnxeZwDqP512zyXw3UXe/OnOkkCaF4qOD3aGD4yn5S3Nr/qWYMAxvsoLT032qjPmKTURhG8L9EMcMjflDEo8ir9zoLMmQr94E/fCA36z13lL5HxRvB8uub3QZCh3TPCE8CbWkom4Ef778VlFdhKtOs+geJa/31Yu2o0rIwyWel2Wd/6aYQo+RJiai5rJC/cJlGpm9UYI955FrlvtQbvf9QRaiDFSwbfcIxCEGXREv3Nsdr03/9gsW+RylLFxpOvz9848jxsoZsyjtijhv400cza4V7/GRFXVEQs2AuSHaui6ycBRn6n2QIf5Az082AocDkoHp1daKfMeMI7fPDi/x8p8WXrJ2Ip96OmDIsl+Mzw0PnefxzXK2SPYCYe7wgyTm5yKtuE6CQ9mQxfCXwmB3MWh90kapywTvgp95izXi7Q1NhXmZiVocLCO5jfanqkxIBQ5R+UdViKk3Oqo2vKQJzTd2QOBr7YGXB6sMnvMQWvRIzpc3Kw7rAGMVHygGdsyOb4t8Gb8XPBpzDkB9EPdhhQNNQ8gKYT9ZguM/UQckrObnCeBka8YiXLMC/R/8UjKrnjP7Pih/wxN1Jy+D/rPtYQGtZPiWoIjGXi47SQP3u3q+9pDQAi349D2xB7TkeUq0GcjiaW4I93hqp+u+uHqKKQ9OW2RAbsx4GwsLd9j5WXXbf7AzeptfjJPRK5HmcltkuqEYooxEh7g0x4PTfObA93rPBiqQC7BZqYHVAaRl6YNwfV2h3YPpsuDo6NOZ96qjUMvTrT4g4DwxtFuJCDYOVdRHggI7iLxuBKXqWh0XK5VWLlVxDLRHccfTZPxR4Iv/OVRNAqswBNTqODnCah8nRMqaMIfQUeoYOKD+KNrqN9uvKK902Ls+NKaamhUaIQZmGkg7B9vaSDJZHNgvCJuwnTv2sMDMGnO4+nAjJHx5h5xPWK3zcFIalROYLkUzqzI+cViM+d00l6ffVIvAnENSHIznn/+2kndYHPBRk/iH0poszX/EfvDmyKDMZPHnVcZW7iBayixrnzubngPno+V50+9xueYJ0L7HhpTlP0Hm/tVa5BMpjHY3Q5xNHkju5n96+fG+dePTInFtCFH84hGUiGP+XJ15hgVuwJ9lHG7lZr/JsAEKhIfayd+pqCGZO2N4UDrlBUTDSBifrP0yhyA9GGnHEd9jYCNxT+CWvDYOQSkiZKBQorkYl5pMOt0luEjtRzRFDFHNSYR1944cqLDHNV+1weovAT3FGPCNWAHT61CsTP0ka5v9xtJtjysnVXsm/UT+Y+KtWh5Ryd+LIgP3W1Gnfk3jxgNz25OWoc2H+3qYYx+k4cf7t0WMFF8SPt02obuaPfEpnE9R+w9BS9ExTCa4IsUw98onyal3uZsz2Lu6QrcFpgqi7WJ+EpPaKcZOz6Pet8vbMUYCcRpS0gpBImzm5F0weJZa44k+q7U0RC0yhywh/af4nyO8LrhLckmX7kesKOpNnXENuj/C5oTTKpMzYbcLS8ywrAmXo33754Hyircg2Zf12E9KV/pYm1jGimsp9Wtku5+eSTZVKTvsFW8egqlVKANX+4hZJe9OLCpSAbeILKPX12LJOB3PeRm0APDnEo5OcVc0ouA2HrzfnmnR3in+oWPWxm65l0yn81FzEuooXB8eX+G9Jy/CorGUp2P//1MZLQaUwwHQUBeSxDYI/3iB9QCRigxCSVQCNJf8v5ehIL3RG/yvcoxlgyi88MZ5DvkFyYj9yrQs5HLeLd2zZ5TOu6Vrogka4/eDJPGAHSmgJlnfutGmq7Cmm5ze0dy1oPSvaqSqZaAiKxY25oY3QTe3FQkkXH3UiSwDT+jHUJN0rb2U0/VYfpgKbI13XHN/WnUq2j46kX6MQWSOS6+Hzeyj0Zpfz/qqY4+WJq51E7bWiUZAT1MSsu3MtuwkWXYXMKzJouDEZ66CSpgW3tDgm3tkKRwSTJwF2eoJhmVAhU0TjjtzzJpyMgN++lEyg3r8B4kD9/xwnL7XXSl7+C7yFqWPMGWVUsJYjdNsF226bGEgBvK4fkXE2wPbpLAQbWYKHTN5ZwoFK7XEPwPULlx75nLo0lE+xMEAdbDgb5dwBE/IReM7drV9+p6JAM+bhl9P6I8wee6BjujspypjbsHFClf0gcM2+mxeT9UfUle17tIhejrmUgRZwz9P1EG8L1AhPou8p/cQ15xaEL+g8mPjEHFL8sr3ncuIQzpCVYYrB5OdTjKP8GewHq7w9R8fgtMzUkHE0D/yvEmtkCfJnsTfykKfZgAy0mSN1+bvtXIWYcJGPNwL3ueXKPIpJ7lVVdg3bz0KKY1g4qVoh5yFIdKfYMhY0G502YPadWLkBTmTuAMC887K9mY6m5Pk0iPXtUNIjkTJSZYYJIsO0ikDKLFSFxqfLhhD1LeXr/YpAhH33szTGyRahVWU2VI14Np2OOdRKsOqlK5E7NxaF2moKmjMWY7CXZhs8OiZWR2oEjakpgJxYtbU15pKPHgS7vBpH3ule4m7ZZLW/VId8IXhkt34iUPXKpcb0rijFNTtIu2nQJ5hRidZ53JHvXrnaKEnyQHA21DDkWpJqJtusFALLNHb19yPimT8uxKzI5DL1a2o0Km8cnCbad0I/Pr5WbD0Az/SuQOIZRStAVzrDTdhDTNYC6ndHyEoWBwE/GnB0geCmjfP3iGXpryYke9lIdtysPOnhdBx9Jk7DK46LjtaBonjRpbSeko/8QeRKj+HxfjmuVIWNGdHwMlV9Nm456ogBLh1G/dZ5m0J3ueQME/0JegHkJVSwiswhYHnKxYpVF3u/bddIR73qHd+303XFfRTRIDCOCbxK4RHY478e6PYagiZxPF084ITB7cnH+f6MYndpIx7BnnPDNHFV1zXQrp24aVK96LokvMi6Iy5mfRcbtFLfBmpGueB2PuvMOQs2Io5fulZGVV1CkwJ0rTyVcFPn6YSf+88RRP3KiZVaT8Vh05yg7NNg8ov1FLf+AMg7ni+dMHEzMCgaDjw5wCDQa5v/4S0PY9FwO52yW1T8Erwy7GjVkCYG42KK1Y07LKrcAwrOQsOLrB8D+6KQ/narFGe49+2f3cQ+FhbTunc7RzKim7wZ90Xl1cyr5H0kHoz2QA5Y74CK9tyEbGSjYyBfuVnP6P+kUT9+XndzMbydP+NRc7czxIWB6Q6jCRYhqKqevmSH6CqVG1DZPO0Lk3LO1opiiSn+TRnMSRwv4dvBx603IR9e8o6l87XvktC/sXpzH+H4szeiJoSd7wQDM+Plbb+ITVWFdzSO4dhfIy93dJJmLqsjR/OsUP0zziQ+pRT+KH7btcTtS2JWKdDov7FWSKTYk6jJVAlYuXdTchi6+cx/ulA/4P3448ITceRmItSpDx4TKhXbq5HR+Vbp7ANGkZgXIo3mgPZAO7LMJtAbjTTGafj4GdolZqji/XdLFkq/T2e7fi1KecyjnUhzDpl5MA/0+a/Dj82JgSwqLR/jUI17I9SAvvlYKavn96lD95rgX+dBCh7FAwD5xDW0IGh7JjxfhBvbKEHI+edK4ySzP7M8Ru8KU5VyOq1NEiMZyqT+h8RaH/UMhHYBz8oswQuH06gwosxugPL4y57BPgSHQZ5aliVEBwf2QhF/KiEO5Fu1Z/hp0qEs/yBlcY3695P0lhNvn/m2g80MayD8cyn8PVnnXmdI7HAZJ/23qW3FDZob2q4NY65Y5BXN1oHrpWyh8zy067cDh0RwZlmYNfux7qiub4oTmu+5pnNrBBfVwiG9Rr/GJQTlF2NdvU3/WIkmZ9W/6mGa+FFXPF1tJCT77SPKtAGVcDElJX9wR1snPgBFRYSZLQHaZxaSjeoO8Q4yfv8EKtFa1KQ4ac1zQGty1GmFJma7cuPs5Wd1KZUZhxSw7ujnFwcuab7pzox0Rojkl3EttO1waHgNNoU+49AytpXdQBn8aUnGhJXvQ8egIWZ2qbnXHc2OASwI6fm4nr/lHiD6Mz27CH4QZDPm2gQ9t1UUsDmVh7GkdOx4GOvx3PGyJTCObEcgNmhAk7vlnanbPi4Hb9n64A/8cvcqIgwsAmhK/RtaTXgDITwyDMgRFoPn0v4Jh27NtkVC4t32It1RRUrdCl8OmcBLw8n7wJK+QJao5aqTxBv0FtkjxBH0HtTnmC/oDaTfIEnfo0rzyx29AGgCegt3rV1eg6A4ffcYNSpvYRe7QfNiaCDqyuVgjBZXUJH0byYSwfJlMaIEJs8ISDncXnWk49Mki2GcDpX+Spxqfd5WkmbtGdhEVD5pn1qxf51fus8MbldLZ6FR+qCKDCEkHsSnXuGr5YzYd6vrd6EfbYXHJlUFfb4VA3Nx3+pxGaxepMvp7Fhxyc2uraPDiEdugMcMFwGQyQw8DnUACjSRzXjsEUVqsxalgNZqpB4Me+TAmbAdfX2OmA6r0vfI/Zq678EHmourIa5bRw8dletTjTF/b19Ko+41HsvvCtaerwzPAQu1psXB5LsBbFmXElsduhWKxMCZVZPZF7voEHi6OdF96JOQdWkwqkrsbQnDb1ref6NvABbYpQahUN+sqDfGjmwz+5SVVMEJn0xZX7+ayaD/35+9fS4YFMzFagzp3MJT+kx1ce4Lec4IPGtcLt/bq5GMF+BJ0lYPz4dhI3qyu/lvdL66JYeWON6ZQjjaeiDNdNPH4pj/vpqC7YL89/l0fctQ7tTwIh1vidAL/LXsL7uk3XOy3gkh/Bs7/LdxylI2K5Rbfd+lGKC4Rrg/dgdHfcfVzKqjqbjPu51a4yK4ZiPVNdqy6wUtnQedCemrY51hMIWmubEVJDiUkaOb6wopExXtFibXu2uk18oTAr4gsDsTJgq0vMQhfHwiQ7edjADzpPtJsMdFtRhmOG9a6nI9bvX3auH/QfXSNM8Nyt/nGbPOGbZil6v2/GYspxaaMOrXuf/Wz2BrqIMqSHpqdNcbGBXmHZ9+9eJuF4E/57xTZfRbXPNrQ+0psWf+3xWzANr6WKivyNiihJXrEQu1ukFpWgi2zf6+DgKfsvhRTB4uer9WCaRF/FLvi9PeIMbeBvdfGhJWJog9gWsUe1vAz4ALwSFrEo/iCMjVG9Hoqw5OG3UzvDf1jLoGZduWbfDoMHrfRcVm1bzPU2oZVokwuOYZtcp/Wthltlr9AHB+gTvUmLxew3vLXRBa3Zyy0nqSD70MXHXfgl/jbK/JnGSqxQhnjLD88iIzMroXVo90XYsLAgy6u6v2PTnhLaQCWDn6MZUJAZcPSZy6IZEMpit40YSbsXgiSdsGXyAvqyVnW9GdcHsYY5axDhdeFyv76tVJqY9pQZVipDX5u0idg5V/NOeYKLgXaTPMHFRFtTlUjP0LqTaKZFSNCKdMTEJ7RWNckTWsW+lCe0vu2UJ7TybZIntCa+J09otVxFJxz6rRBmdNPmL5JNZ8wdqIyj+OqyGgPIb19RoomTtZDlkPORM4agXq/kN4M2K0EEg/sVcbtdLn1a7jdo9pc4FGtM7fykh1kZ8B00c3iFVZ3POTtmdAU50KrXM/a7mMvwK3jf2e4+wTBxJo9fg51VilgVn0CJ9IpdpT30bZzGwzAscwzksnkywnKwIgrtimsuVjuYhNuJeLW/IibZSQTjc+cRX5YZ1ATZoLu/poSU0Uzr2IjIRxVHZl6r5K8lR5lcSvu0U6scySE/O4HgtRCcHCmEFzkoP4ktDhePs0NB+d9luoEzZlUE3tM+lylGyc/HKFYjhykFybNVmCxviDRCcfJedY3bHBcn73kfgZnVUCYtL1cJgaznSE0CRwWLGlggAlPcR+qSAlaxEMPVIw/CmTVg8YhPI+Pgpz2A+SFvI6yIgZje0K8G8U/THX1HpJHGhGkQYXHBiTUnBTWmOjjNhBf6Dmb7DhjeBwPDPbIiPY7UmIOLRB0Ub2nsvctz/qdknNiufb8A9xUTveIXet0nh5ByWj7zhL43+8RmGWfIMfciJLddAwO8rjW003qJ37WG9szPr5uNzTdL9AvMVIWW2u3xL4BGuQN9RQh7YpU5cNaqpICNagQ1TlZDFLPfpp0DbsV2csVC32M74aXa0mQDcni/N3s0tFTzmu9MMieHfjQHQMn60FdxKJjoEVsq9ICF/EV84gdXMjxsG5rsdU1I8tqGTkhSk73qhCTt8V+x9VuMBJDj93Vjg2xcBtAz5Hgw4gP+GunVNj7gMG4/Jn6XbFLaKDLJ2h4XOQxxtMTM29Z3QiVt4x/dqEcHK9mF0uvpeq+o5ki48I052k21x3XeDYOT8dvp5M/dykRhJto0F1MiiagzvbH9j95LsQRYmGf+r1Ev/Htpu5yTo7SLTtjhF5Y5JXHRCeaB0eiE5BIZndC3XdIJvn1HXooJlKKL+awYztrWoaJ6Wpc2iS9q46MQPtnbLT4KIRaB4O5gPZOhGcFbKAyhTe/flke9n+qays7/fTE2I3g2hgBkXEghAAhMVK/dNN1qigxXwgWN0FqsqGLzFTw5lOK2QeeWPkld8G1a0yRclxWrlpV8Qq+UrRqGrRrmRpYzw5Fg9NHXv7XqsdVB+u2VHXRLL8ssGY13flOUmnJo9+gLDIK1lW/BznnMqbNXnqaMPIOevHtuRya3zJgXZI640amFR7XiRtstbT0hcwjYWDs4mm5ejQRHABzaz/WS6jL/LFiO/a3Pi5XrmDqR6zzJjYPR/W1PN9yYw264ozbqe9ogjZOZcfFInbRoz6CWUyw+8WEevGMI8xhmHCeDO/XxqrMZH5wBnkM1OUVil3YhNCNya7HY5MEoVnT6TL3NSput7MHZZifYtqSWyzTdajWV7wver4jFtLCxg+759b1MWrKO23K0volyJ0IhqHNR2YgMiIJMZ8s1Xrtq3Sk9bh+/S5y1QQmtpMJIMVPP5sAlbCL2z+7PeQNTk666Zg5citF+lkH7blTmc25FKqvP3UV0salil0EXGyqYLuKIYqR0e9ipfb6rlfZURmpJ5pPy1+tOpDDQhTyhx4EzXLlBu468+G+4g7097YTa0sCFv1p3XM/dGptrh/rj7Fgx/AxEellFh0SKRuGR63+5jneOMrW6PcfRjcoTLrkCZw7lgqgb1qpjbFhqNDYohfbG/9x4gu0=
*/