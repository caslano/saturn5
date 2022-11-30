#ifndef DATE_TIME_DATE_DURATION__
#define DATE_TIME_DATE_DURATION__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/operators.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/int_adapter.hpp>

namespace boost {
namespace date_time {


  //! Duration type with date level resolution
  template<class duration_rep_traits>
  class BOOST_SYMBOL_VISIBLE date_duration : private
              boost::less_than_comparable1< date_duration< duration_rep_traits >
            , boost::equality_comparable1< date_duration< duration_rep_traits >
            , boost::addable1< date_duration< duration_rep_traits >
            , boost::subtractable1< date_duration< duration_rep_traits >
            , boost::dividable2< date_duration< duration_rep_traits >, int
            > > > > >
  {
  public:
    typedef typename duration_rep_traits::int_type duration_rep_type;
    typedef typename duration_rep_traits::impl_type duration_rep;

    //! Construct from a day count
    BOOST_CXX14_CONSTEXPR explicit date_duration(duration_rep day_count) : days_(day_count) {}

    /*! construct from special_values - only works when
     * instantiated with duration_traits_adapted */
    BOOST_CXX14_CONSTEXPR date_duration(special_values sv) :
            days_(duration_rep::from_special(sv))
    {}

    //! returns days_ as it's instantiated type - used for streaming
    BOOST_CXX14_CONSTEXPR duration_rep get_rep()const
    {
        return days_;
    }
    BOOST_CXX14_CONSTEXPR special_values as_special() const
    {
        return days_.as_special();
    }
    BOOST_CXX14_CONSTEXPR bool is_special()const
    {
        return days_.is_special();
    }
    //! returns days as value, not object.
    BOOST_CXX14_CONSTEXPR duration_rep_type days() const
    {
        return duration_rep_traits::as_number(days_);
    }
    //! Returns the smallest duration -- used by to calculate 'end'
    static BOOST_CXX14_CONSTEXPR date_duration unit()
    {
        return date_duration<duration_rep_traits>(1);
    }
    //! Equality
    BOOST_CXX14_CONSTEXPR bool operator==(const date_duration& rhs) const
    {
        return days_ == rhs.days_;
    }
    //! Less
    BOOST_CXX14_CONSTEXPR bool operator<(const date_duration& rhs) const
    {
        return days_ < rhs.days_;
    }

    /* For shortcut operators (+=, -=, etc) simply using
     * "days_ += days_" may not work. If instantiated with
     * an int_adapter, shortcut operators are not present,
     * so this will not compile */

    //! Subtract another duration -- result is signed
    BOOST_CXX14_CONSTEXPR date_duration& operator-=(const date_duration& rhs)
    {
        //days_ -= rhs.days_;
        days_ = days_ - rhs.days_;
        return *this;
    }
    //! Add a duration -- result is signed
    BOOST_CXX14_CONSTEXPR date_duration& operator+=(const date_duration& rhs)
    {
        days_ = days_ + rhs.days_;
        return *this;
    }

    //! unary- Allows for dd = -date_duration(2); -> dd == -2
    BOOST_CXX14_CONSTEXPR date_duration operator-() const
    {
        return date_duration<duration_rep_traits>(get_rep() * (-1));
    }
    //! Division operations on a duration with an integer.
    BOOST_CXX14_CONSTEXPR date_duration& operator/=(int divisor)
    {
        days_ = days_ / divisor;
        return *this;
    }

    //! return sign information
    BOOST_CXX14_CONSTEXPR bool is_negative() const
    {
        return days_ < 0;
    }

  private:
    duration_rep days_;
  };


  /*! Struct for instantiating date_duration with <b>NO</b> special values
   * functionality. Allows for transparent implementation of either
   * date_duration<long> or date_duration<int_adapter<long> > */
  struct BOOST_SYMBOL_VISIBLE duration_traits_long
  {
    typedef long int_type;
    typedef long impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i) { return i; }
  };

  /*! Struct for instantiating date_duration <b>WITH</b> special values
   * functionality. Allows for transparent implementation of either
   * date_duration<long> or date_duration<int_adapter<long> > */
  struct BOOST_SYMBOL_VISIBLE duration_traits_adapted
  {
    typedef long int_type;
    typedef boost::date_time::int_adapter<long> impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i) { return i.as_number(); }
  };


} } //namspace date_time


#endif


/* date_duration.hpp
ow5o+uaE+LqnLooRIF1whhBiz0TA34o6wfhDo3xYQfJZsssnSVgc6XFLtx6D/0CKFh25hxOQOCh6WtPmqFeznjlO4WSzBBpEMQzMk2oVWGqKtuWs++E+L1o6pVyG6bu9niozzeE981kkdK0JFFkrYNAsA6JWKHLS6LN1+CCvkXYvdy096zV3tbYFKeut8Ow1zEjSZWzWC2p/mrV6AbJWmGDje6u53rczIZ0K2krV4l9mAXUBAID+AP8B+QP6B+wP+B+IP5B//vsD9Qf6D8wf2D9wf+D/IPxB/IP0B/kPyh/UP2h/0P9g/MH8g/UH+w/OH9w/eH/w/xD8IfxD9If4D8kf0j9kf8j/UPyh/EP1h/oPzR/aP3R/6P8w/GH8w/SH+Q/LH9Y/bH/Y/3D84fzD9Yf7D88f3j98f/j/CPwR/CP0R/iPyB/RP2J/xP9I/JH8I/VH+o/MH9k/cn/k/yj8Ufyj9Ef5j8of1T9qf9T/aPz590fzj9Yf7T86f3T/6P3R/2Pwx/CP0R/jPyZ/TP+Y/TH/Y/HH8o/VH+s/Nn9s/9j9sf/j8Mfxj9Mf5z8uf1z/uP1x/+Pxx/OP1x/vPz5/fP/4/+9bb57cyvaVighM5inFe6urbh/FsMWpWN8E7m64D9qfX/1TgSFkoKV69vM8nh2J/dC8YJMxJeK+2sv33WbrcfFpr9HHcS/5sB139mit/wnc0hI1CQUO2Fsw8Tql1hWJkc9kh9tFegSsygoVIWbldnRw4w8PGMTS/3ObpmydX6EkSA8GfSqGhP9HAQkgX/zjxDh/S7UmDM/uA3cSKi1sbQ4nS75wQe9LzmwMZhy5bdCrfqIUyPlMbPWcBE8I8CHnbNGCdFCPm3lpR6RwN7jkI/RzTvEjj0sHgGcStI2w5qPSN+cGDocFrkDNz8uNBasO602gO3Ca9F+AFkpzd+7NrqUruQwJk6Re93ObPahoYRM5rD8rtKDMeapY2+jwkjzg3ZaMKk84pjv7y0qtF4/mf7y/kq9LKh8/gQ91ijhgN65dCdR8uSTyhQ45UghnK9lf0CCk9VONbKJW59ucGhyuAgwj2PJ9RYhEhvEcWxpUoC6EtWY9IrP80KA0cUhLAuq1bJc9EOHqhf3cwle0YVzEaTW7gwqrPxFfAPsSVu8YBR7f/DMNPyQN1FwwVvt59+EQMxyi4wQX+zGIzqLLGnTSD2OHwYzerRc4griC2RpG37ENpuq+MPAd5oEhX6/m0N5ABek4ghj5CvonEhTEnWXXDFhNw+6hzhOOZ9yckCh1EWw9TUGuqherqF0qYDFc1mxQVAMcSThK0Foi0FFWLiErvkOY0OQ0u/sKHLvjmgAlrP5t3qmVq+2gP6hqvhmhG6OCJWNQjlZVk4XXExBs1+buSxh7KLyBK0z8Imd8XbFEVoNnFrnZUc1HoqoqW/gZck834I0kY/WEM/c+yLLHn2evLq19Z5SWbAJhA7ZZUmc8N59W1le4H5WevLjfef9dWEKywO4wbEvFpbb9BypLJZFd8P1fbdcM66nYfzhuvav6YEqIxBP7q6biE6iOcDjsoIPr/IzJ5WK0cDMJMdjalaPAwnpGSBP5u6ETUCY+sDBXnJetEGS4WC4jQUHWKJqXfmhJ3PzJVd/PkxznCJPvOp4kbIdwUSJe6Bfdl1aJR+hNLYjFOR/Ionb6XlM3vqWLc9Zz8VfUIruIN1vVnz36Y+lzHkMw49ihkeiKv+yOd8ghB2RMxL9R4apVbxzsNQVGRExH1e9SPo+g28krouLYppDhQE7xUkRrFe5My+0h27Y5i6U30fKSAiZobCEm9Pb/AMgsZn2VtTFf8vsd/eudkXYLfGf0u5xmxKZsW1eM1olbXLYwXpopAhx5L+4g1lqqx+D9f06tCIz1mwwCFzyyvUj64gLez7vR9UxVv/2ojm0Xkeo/YSdFquckorCohYNqcOqcf1AnRAkDdtAwmZlrRws1mZSrkSN3ObMViPUGKnJ7KQiuEE4rKHXIYKX80mfkHrLLNZ920FeCBaO767NGqgzgj/qkz2dR7lw6ADYgEWGMh1es6MnBGDzWzwKrCyAqZhrUKTUNR0Fch/ctX2wkJeFjRS+eP9INRonmPLM/WWoPEisY3+pT/1MBZQUM1xuQdmam1OLP196zrCVwwz/Pe3fGJQ6ZRgs4KbhsDUHCGHae+en7iuu1HIRnII3J/Oe2uFEmliCDQe9Y5/3bUM9PqbrjiEoQtiLKWL5N2lxTIRxdIwFEhybsGJ+SBXdE/fnSw4RcOI7IEGzeCY8KQJUpm6KNQWRfU9EQxOy2zqF5iqzk3hEL5UV5ClWraizMcNya/LmPBKgyN9qDxHpogypTIaN9y5+3HSLr1GgKV2XQPivkikJDSHTBAxddhuhswI6r+l8SHbLXP/eI2b3tofrFIGWMfqfjE0UsIIZEXL99Ml3uPKTxAiBB0s6HhdxlMNAtmuelwI0kvkoioCDD0n4Jvwup4uHg3/d+O2eYKMrivA3+/BnyCskqunbD99mAMpO2/hwZqwYRMAObGAQSl36fhJsL+XDnJv5mX4fwXqBJmWZjQ5vUcbTNOBPh2rIW0O8n4s22HB4D5ZMiv+kP6ZIwHUuI/1DSC0x3h8TpR0I06Z/fRtW4QYR5u7+uQ4P6jGFRaASSJIiMYIPRb90mmD4vJiLPT3W7JwEUL0ONaLzEDzLMyLtSnfw/hvqVsSXSXyRVHoRRAozwq8eCP4obw8aANOTQdF0zxq0FeFX+VV0s8TI6U07/pCRYl/LIxINL7W76YF0fIfOt+g5IZjdsewT1ujrKKc+1KVJwECTmrmUzmG7DznW5x0IJipFFiOiVli+itTg7ka7pk8vu+wfigOVRWhJGvsXJf8FeXkUpcgZFQHEGTcINvYRhdbRb3p5MajHTgdKW3J/6ci9Mw4M+Hz5Xpm2YHCEjcZ/uL7Q7XYPLacVZx0MvoHfPpIXRKgxp9UQMD+oHIP58AArsG11hkulPmSKUcC2h23h/DiR2oJF0S2F6ddYDxeYB32X+aF6On/54uNVz1Sy7r2DQyKNxggn8lzHXIuyGs3QGoGKhthEF3+ef/z0TDa9uuYLO8s2pdfj581oJA2q3X2V4J0DXPTaSk324o52YvBN/kFfXvDEZstBz4HNGO+ldV+Fza+jqe3s6fAlXaIj75c0UvO+F07GWc5u2COuzbQire75zMwNOSP6bzOOs1svgJz8I+prkir/T8OBom8Gn7rTsew3k4Zo+EidRb14LNOAtpqKq/0Dp1FsF7IwCk9BQWWphG032bDXmcT6doH8mf2soH4fe3fl1GC1LW98o88YaFo5s65lgIGSUR1J2FM5btBOCaM1TRoOR6M6GbxJTzmA32V2GFCckQEBgJGJ5Hi/OlnXHFP0KSMpw7UyuGPl9Z8F7i/EvylrXVPKkQDRdnE7ebHs3n9cwudhdK1CCDLgBa2pVAi67Q0gnMsvwwpeEShxcIinMz38DVF/1QT8Ama7Z1RTKO368MOiogrtNS2X5dHlZ8rijkiI3Y6fwxd63WZjcd41CDUE62h8dCOjovgb01UVVFXJN7o3LUXqO137koY/fkjdA7vgS75sY6bv+zYf6AbQETgY1l4xLi8Vk/de0vedMvrPUabzwe49QQmYHGVWS3GQ4kx9m5gyuZ9Qd8r2KkkgmS6HasaK4HhtuOVa2HAOuHfvYHrkjQDoclSzClYNSXxvzaCl6/+ydI+cg2IRprvyhQN8R/5WApmmP/kXu8o76Gtg/HA70i+nzVq7HXUz8izDRNCUyHMs5muPyAWbl3er9qpWY8abK8UtL9Umdwr/Fe119jqDR5a1/2NU8DOK7RFCY71/HnvU1SWgc2MA6uuGqBnOxXlE9hZ0lDN0eOT6aml8ViKY1Z47qQuocermIdcuGtlV0Vwvx0vA8wKhUB5iRtjvG5p2E6Be74HU4guhjjQ0zihHsfK7UfPAuZcmgBFyeO66KkaWp8fmR7hY4pNsI7R1AJxwNuhU18Z1NQei1QhlXRRBFd+l0U7/XScP79KBnXMPTaE7hyCWdXodmsxBZjH4IKfk/c4rW3ZHF1QDLUPYPbDqeh+aO1hTYfH4X+ys3nB+2tVzudIDgGR3tRUzIhGEfdnQoSOcBF8fYYenxbJP4quska351k5O1fSbHy2ndGsamoDtUo/1a96f/iM2Uz247d25+PrW+cpikqWIi9t5/TxhleGj2JPaoDyAdGeT7Z84NYdVq2nxY0Zk8nCu0rCL7mhlmpdpwGN3ni+XkUxLrA9bR9HAk1j0WnF2BkFvObL1jNmS01DuC+an/Ox7H/UKrn36DP0dIK4d5/LTKnA/jtp72M7qUrcoUKZNZt0N1z8dh5xAYuy2ZJPmae4yF1pHN7l2u0WbX3AD6suI/AwGNvAUV0u5PHwTZSWWpCLLibDa9n1J1b8GnV/H65Mf/x/HrMIZnwTEA4vPYq5bMZwjAbaxHb7C4EpdYPAFh0Dqgs+B7oDyvm0UhWvVGd5rmAg4APEYOEF5f89H4HsDVeqqrZ4Ok87sws+J3+NXiMwSF1dtg+F8xgdKg+KREicqVWAyjcQzyq8hLZpL0wZ7xWvZt0j+9DAPb6LGRlLr8kVytUSx2X85BLRbp1hAbyaZmWygbzGYqKXiVGpwU9+tpWZE3ngLvStv/Pg+7ud+6mefULILzifdh6r1l8Fko9o+OTrbHPT4Zl92l5s8nGPE6LJO8b5k0lc8p3VlR1uWNIc1HOoRez1M1JE5XKR0W/9MG/dd2iqdapHpT67JHsOuk1amfquptB5EuAD9H2Vj3ULSYbOpaTP9P4MTgqqjPYucfv9A0sDU4hFwMuTUjqUl3N8TNi+N1J920Rv+rYXaSdk/o9f132PshidbYSgXIhvTwHZ5PY7g17lq0eVXS175EnvjtYDHuzT/dnCY4yllgjRUm6CHEHREP67LdbAwPMVkmLgrXm5Xync3HOitZfNAMDKlzuf+Yz2nx9iKtbcg3XksRlVrZfUUBhK1pJF8Pm9mutcYX4GRU9FMWCS/oDa5ekpm6aeU1DRFlacxdUpKJvZXCnj5FoLXzS/AhLhN+50ns5TkNBGemx8fEE0N2V1tpCtW1t0Bjs6mrUk8xXlhJZvQmH1f/UY1Kxa1XyPbRJEu94QqZPpuIv+2IxOKuCCEbqzP29dZnKyOOboRLwIqfwhp/t4FosWTCF7sPsiQZo25w0Li7s169Q7kbmeyGWpttRqu8bGEHh/S2NIM/EWeS+FPYVcEM5drAEzzL2vQTH3X8FvWXtwPRZfHJ3dfzMZXj+a8r91C972S1pnpXWUtW9HX0K+BPn4i30++TVrjUhKqB6/jXlnPgqSJlvLgV478mQc2GhMFsXqOpFLORpO5btgw34Bmvo7W0Grt/RZnjsw4TWaPCJQxeyKHNHO/h6CkJooruDyE9TK4SruFrhpCXtIYOw8myW7Zys1Q4u6+Mf9Vf1lePHg9vokjfctjV5W6xV3OS5HLCRsjCU3GTxnlDR9ocDa5NOyX9y8hkNYCNcYPRZgXkM9BHSheC4t4kZmpypTBAnwPRzR12Tcu+jqB7QN8UXltrGOEZuOZ+MecrgscK0rh+McEUKMOCvhSguZ0U2Jsk6wmwkPevJ2r6TKvvLcQi+m8bayH93/hM4NCEMmvNRXOWbGeYzPRCo2LPQxW0mPO9QsI6kurOIP9uwzFJQ6pN7ohPuEoSVI1cJIpR0nowemKKUvYENqbDh75TBYkza097+YI1noQ2FPRrqVM0XW6beXXu70KcBeNFFowJQId/AB8s4NOZWYtn7Cqc1+fLZkDIrpZbdlfkGmMjpbSHDCtGvAaznoTUaQHM9s4vv/ndEmqMHP31EpeqA+L3Ah+I5FdViZWPC+rQLsCvHtMHpLBvUP3YpxFNm9NqOVd7hgW36kepG9U/h+sf86X/jjf1s9bkLIljcUtY6+wf7B/na1yoBKgs9P3j3H2JRVd+yhIa4wHH1bmputcFEFLhQ4tmeH8T04GxiBcKVn7DluCUTImcT1mfVFwSeUF5v5FGUDSohTYfkglAVaZbLCEM7PaNKqid/K1SvIIbpuZChHxFk1hJwPZt6Pp5heN7J/y/qX7w9OdR+nT/b2nOWXvS4ajN4ZvoEgt7dRF29w7HNRV5n0UStGHNC1ZAsvpjfWdphC8vGXXGlZR8umDZHVYcFeIgHgAxndS02w69Jl9X9vA529XyLuyAFcQ+u7aSzrkq3MUA95iV662pRLFKYm5dwTG4lVSNZvGSZLzRdx0r36As9xMtp2sLjuFg1Sv/DITQtfrzFBU9G47ceAc8yI8wdqYpvProMVSjnt6eIFsZokzug08UdpEIzagvEAmd1o65BnOGY9IF3kCXWIjZv0TAk0aFxg8kLYp6EspcqWWsPoJhikOZP++MmKGCfufDEa81gxKMlpC7TWUjwiSrAuZkXs0KRFrmpoo4bR//Pn4foa8ip+4+KdmBxFkk5SKasHEoYmPM0TsPIL1QyKR0Ez90TAYWcmcAxpJqvHd9tGBy/2AXKVuLqF1vKMEOz/D6liqGBUdEB/Y4Q+eBXimXh2filMIjCEDYMtvIgZQF79hkOMoMIejsGqKrF6ROiEfr1Dv+GxDaZDVeCti7Ls2iFqNBYYhnOYKATllqimsGfPqcZW/3XUAHU/gzgFyoUp1qV0na8Y18lDUSsUI+L2oUQDB/l9OZHKK4M8mtLBySb9moLV3qPmyx8l9aBDTNsTe0uQqVSu1GJQp/6iSqdzAEQswnZON66TXzvzLxH06c0sAJ75laerx7EjVSwydOfW43HIRUuMsyhBb3jNjMuSz4F+1wfKSB/R62XAktNBg+QCRYp/09FMjx3pe6fyHCODch5P9lQ37LWzYCGpyHKfrx4NS9ig1Cg8/2yjUVea0wFgV1f4yv3rTjXSB2ijzq6y1gxBLUtJSholvT82vbFS7MIVNW8SevMn0O1vgYRNeXpq8Z1C/Q0v3Y8vpD7EmbbBq8DItQits9EhdV6wa06Ufw5kt049CxuVXC9QPq2v6S61eexEO4udgLOX6N3vOT96wbrgnt9TA+7DqKxcqfzWrA6SyIx97Y5W/QM4vAiFyyAuYh0X7+++9Z6sxVb2cza5pzPnesqWjPhFIedtoTTOCMnvR8Ze5WHHfRuezGlHITZ/uAD/ohcZLiiTUqP+RpJyx888Jy4JJxwPhJ36aSWh6IuZZndTXBf35vXWDbcKOLGWT1LpJwAUQr9T2bTxtO6e3IUmgb2zZn9U30EfMSi0jrFJIMNJnW7T/v5T2REdWJ6IStQ2Vl7yR7Fi4VLT3ZDCUu6GkD5yK9aIZU0DGJ+9HZJPrMWjWE+4Ql5SwjtXSIZSWcwgH9fwRQTYQ43kD6rfOfQv4CrxvzUTVz7v56p1CpzkI216sIbsuKYfoiXe2QWA1vSGyNwt8+umPl4REr4iYPY1/bxsrLIx7hqdtId1gzppskuvO5NxW4+ugC4BYTtvggcF2Jd3SeK/Df15g1UBlr+91GOibMRC7ifjfSqJ4nplok8o+QftkzXCeT3CX+LaHNAMDG27BRSbP6b3n+TEO7BkCcta/NZ5f0jseil8rkbP6qPFF51jaumCSQdM/O9Y1w0u8HlFrYfR/a
*/