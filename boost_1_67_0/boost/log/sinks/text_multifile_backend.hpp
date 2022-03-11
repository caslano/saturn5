/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   text_multifile_backend.hpp
 * \author Andrey Semashev
 * \date   09.06.2009
 *
 * The header contains implementation of a text multi-file sink backend.
 */

#ifndef BOOST_LOG_SINKS_TEXT_MULTIFILE_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_TEXT_MULTIFILE_BACKEND_HPP_INCLUDED_

#include <ios>
#include <string>
#include <locale>
#include <ostream>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/detail/cleanup_scope_guard.hpp>
#include <boost/log/keywords/auto_newline_mode.hpp>
#include <boost/log/sinks/auto_newline_mode.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

namespace file {

    /*!
     * An adapter class that allows to use regular formatters as file name generators.
     */
    template< typename FormatterT >
    class file_name_composer_adapter
    {
    public:
        //! Functor result type
        typedef filesystem::path result_type;
        //! File name character type
        typedef result_type::string_type::value_type native_char_type;
        //! The adopted formatter type
        typedef FormatterT formatter_type;
        //! Formatting stream type
        typedef basic_formatting_ostream< native_char_type > stream_type;

    private:
        //! The adopted formatter
        formatter_type m_Formatter;
        //! Formatted file name storage
        mutable result_type::string_type m_FileName;
        //! Formatting stream
        mutable stream_type m_FormattingStream;

    public:
        /*!
         * Initializing constructor
         */
        explicit file_name_composer_adapter(formatter_type const& formatter, std::locale const& loc = std::locale()) :
            m_Formatter(formatter),
            m_FormattingStream(m_FileName)
        {
            m_FormattingStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            m_FormattingStream.imbue(loc);
        }
        /*!
         * Copy constructor
         */
        file_name_composer_adapter(file_name_composer_adapter const& that) :
            m_Formatter(that.m_Formatter),
            m_FormattingStream(m_FileName)
        {
            m_FormattingStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            m_FormattingStream.imbue(that.m_FormattingStream.getloc());
        }
        /*!
         * Assignment
         */
        file_name_composer_adapter& operator= (file_name_composer_adapter const& that)
        {
            m_Formatter = that.m_Formatter;
            return *this;
        }

        /*!
         * The operator generates a file name based on the log record
         */
        result_type operator() (record_view const& rec) const
        {
            boost::log::aux::cleanup_guard< stream_type > cleanup1(m_FormattingStream);
            boost::log::aux::cleanup_guard< result_type::string_type > cleanup2(m_FileName);

            m_Formatter(rec, m_FormattingStream);
            m_FormattingStream.flush();

            return result_type(m_FileName);
        }
    };

    /*!
     * The function adopts a log record formatter into a file name generator
     *
     * \param fmt The formatter function object to adopt
     * \param loc The locale to use to character code conversion and formatting
     */
    template< typename FormatterT >
    inline file_name_composer_adapter< FormatterT > as_file_name_composer(
        FormatterT const& fmt, std::locale const& loc = std::locale())
    {
        return file_name_composer_adapter< FormatterT >(fmt, loc);
    }

} // namespace file


/*!
 * \brief An implementation of a text multiple files logging sink backend
 *
 * The sink backend puts formatted log records to one of the text files.
 * The particular file is chosen upon each record's attribute values, which allows
 * to distribute records into individual files or to group records related to
 * some entity or process in a separate file.
 */
class text_multifile_backend :
    public basic_formatted_sink_backend< char >
{
    //! Base type
    typedef basic_formatted_sink_backend< char > base_type;

public:
    //! Character type
    typedef base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef base_type::string_type string_type;

    //! File name composer functor type
    typedef boost::log::aux::light_function< filesystem::path (record_view const&) > file_name_composer_type;

private:
    //! \cond

    struct implementation;
    implementation* m_pImpl;

    //! \endcond

public:
    /*!
     * Default constructor. The constructed sink backend has no file name composer and
     * thus will not write any files. All other parameters are set to their defaults.
     */
    BOOST_LOG_API text_multifile_backend();

    /*!
     * Constructor. Creates a sink backend with the specified named parameters.
     * The following named parameters are supported:
     *
     * \li \c auto_newline_mode - Specifies automatic trailing newline insertion mode. Must be a value of
     *                            the \c auto_newline_mode enum. By default, is <tt>auto_newline_mode::insert_if_missing</tt>.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(text_multifile_backend, construct)
#else
    template< typename... ArgsT >
    explicit text_multifile_backend(ArgsT... const& args);
#endif

    /*!
     * Destructor
     */
    BOOST_LOG_API ~text_multifile_backend();

    /*!
     * The method sets file name composer functional object. Log record formatters are accepted, too.
     *
     * \param composer File name composer functor
     */
    template< typename ComposerT >
    void set_file_name_composer(ComposerT const& composer)
    {
        set_file_name_composer_internal(composer);
    }

    /*!
     * Selects whether a trailing newline should be automatically inserted after every log record. See
     * \c auto_newline_mode description for the possible modes of operation.
     *
     * \param mode The trailing newline insertion mode.
     */
    BOOST_LOG_API void set_auto_newline_mode(auto_newline_mode mode);

    /*!
     * The method writes the message to the sink
     */
    BOOST_LOG_API void consume(record_view const& rec, string_type const& formatted_message);

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Constructor implementation
    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(args[keywords::auto_newline_mode | insert_if_missing]);
    }
    //! Constructor implementation
    BOOST_LOG_API void construct(auto_newline_mode auto_newline);

    //! The method sets the file name composer
    BOOST_LOG_API void set_file_name_composer_internal(file_name_composer_type const& composer);
#endif // BOOST_LOG_DOXYGEN_PASS
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_TEXT_MULTIFILE_BACKEND_HPP_INCLUDED_

/* text_multifile_backend.hpp
T59HM0VIoBT2GNE2Uc7ml2VX2V1p3bv2+Yi5Hj9rR2On2aJVNSJvu11qpm39WEC2TkjKYs2RM8wgIjJ54JWEfjW18vYax4E9d3u6iepKkZHDrgXZ1KJYrXhpCl6JqBr24yYAvfrR621DRMkfqzweMK5LOtMp5eAdV7MlcjmejaN+pfTihoGbvnC2MsoYmlgiuyAaVLcc+whMyMOEGl+ofx0P+il3PdSMSKjGOB7OXlkYQVw+5zfAFjo+4CzLWK5A55WatlJ4dF+kl3YnHJTkq5OD9g3Euy8pIGuOst603/wKhRNKGIZyimPNbvhI9hJCbCYn4DiKVBW1IxN3esWMJxb72ktk5pUqSWrrqXFzas2T+ESpDxLMdDbv8ZVYj4oczSCfN8GOEnGihVJXb/Am5WTtqGFoeAWmkHHshkAaE/lAfSMAXcj6wCGVlS4rqGfVW7GUblPvdXeECNbs3rVdbTp3etLCmUh4qii3XLF80D0V8pOkYe5VpJ+SD7s6GBIFVuZvKNqDCZUKgykft+PetijaAuXbk1HTgI3EbamQfoRDcqhDIM66Sr3EiKp9vhclIZfW3qKC9TWGWfflECxsZNRhffZ/4JuB88cLv0HcL5WJK3lOCFyBvmXfdvX7JmX6JWrHdBmowW+6gsgvwUFklJs3FHTuXi8eQTPy0NhgmXaUmy9DtisPab741lQgeoDtRL/pjSsDmzVMqajSmWNbjmgxuH/y6rEWgUme2l0pV3HdPHiuxgRxM+AyniJRvRZ7saaDa2IRVGqY3tiu7uTm2YPtBs5MsBvP/6wDzLPeUs0MnQCUubgM0tPfLsN28fkbDIPy73yEjP9hv5bQGa7PVVg5rEwnMZyiPoM9DBmQHb53tpNah0uK2FxIL0his7jNPItyoe7tFKdxsI1yT5rxyoGv9TPGHty/gWhbYPqmP9qu1Yv+6vZJXT5QSXUqFQzGlnki2EQIUE9ma9oRYxxL1uOkIrerpC2xX7FsXugyop33V718Blq79e4Uoz6nAt11co8nZhF0Y9APmLjoOjprfbTnqKgGkTQ3+QUUmc7n0GbSH89HWji7W29oOWiRKcE4LZlqSsPDIFlZuqp9NpBi5xdUp7br4w6TEwsYngROQ7/eUnGxgYf/B+6ng5kNbp7K9zyppgtxEYWZBceE3XCznE7xQCBSTtrq8aizBk1BmSPzb7M8wiO+AwMz9DAAK7kYqjy9tITQR2PNJXXf3nI0bP/tKdkmxHgioS0s6KtzvPnfk+D4AoE51zzw9wjRZD9rVKwv6ugAdgq/tjGoWof7NCPVnG2vK3cNWupEKsgtyCyd92qQROIqwEqpfqne5W1CSHHj9qatYtSahjW8rs15YYyZjmC9oEqVBKSV11CHRv1b08WPWDYGEkzmleIMS/wZaE6Oz7yAFGJIsZO2SacjPUO5k5fTvebHvj5V+9h1sgoSMX8MXopN4BIoR4zDJLAMycf6D5Ppf4c0AsJSuzQtYaI6YENaaefMYOyW1vvaiKX4L/Gt8qs+0Q2m5z1lMMQ5mmqs+8iEJkWh0r7EVjgxQ7iS13dnHVo0ot0NW/lyqitQt+dGrWExI/P3FTOvWICHaXI5PXCjP2aS6Yei0SmuHBG0zjT7OqrgYoc5PoeV1geMk76YdU8HoFMDm88HvGcTX/LWQtMbtSXGDN48yGK4vip54tCjrsuLEBe4C0JG2dgyKCgLHW9Lzde8uwUJMjTbPPeSDxQJspw8/zi3NaJIqvIzV0ZDmCaXIC7GFC2UgyCEQQJdu0PQgcfCYFCphGzgHGO7+ujSG9FwBGShpUsFiMv+i1kt08Z0biNEJ1D+QJgq20DUdVxzvVoai8N//UmySsVlLXH8HdSEEwOmUBq7PqFsn96iu9STvLe9akGFtNqhSzeDFv6kocbvgAsz4uOrOX1mOfGzr1/wZutS8SORukRYxfi+yOXgiIQzPFRHk5e+elCkb1aJGJK9kkHRmUJUN5EFHw5DHbx7L6qnuRcl1W13YGOZJUphZcPhQaT0VkFH6RobGTHMFdWF07ewsaew9bSTDET0j6cDemzETajwsCs7EKQ/1h+lc2BZF8n8qjzSW6wUM6NyS8c9ZQc6s4DUHv58QR9b6N4WwCrwtpsOtiR7WDcZIgh2dOCPWzbEe2UnvI26UH0PpoRAlEkpXXTP0MDp7si1wcPzT/0PkR4+8Aq2ZLfPkPoJYq5Za4APxnmmRX/I6efj+D3q2WoKgs5qbyDT7JjoRq8AiubD75vGILtC+bqyTNN1Ej8QF7wG80v95NTqX1Cf61JCIBeJFbm0OEgl+9b25flAENfzB1rkq+ixbVZ5HtpRWmrp68BTjswjzmgov0+V0dJQsE0GJJ+LIeKa28zhf4kVy0IjomRQ4I1VrDwomxfEreBHcHUGZ/je6fv+tCVYeJtLVk1Nard75txWY1Q6of3Vj4Ad3UX/5VOIi2ddGiE5t0PaSHZtj3LL4lp5pdNjj9EhGqFNsIRDKBE1KzMnw4TSL9mXmN0zB9hp5MbTto5TK/HuVOO6I7NfvaCCbNvQHIvs6tgF4NkTeUBvjdTrLj1qvsBwgcH6otyzX5msaSVSNy7ppN6p2Ti+G1Hez/DRBrfdsfbd9jZYfkYsWZQm++KKvp4AiLp4OthzxivBbNq7TU0dis9v21yQEkXjas3c14Wbrml2EOXYr3ZPiAmz6xevHM7Ps1/xBbh0RLqPOXzjwaISyOgwo3K0mdtFPFvxXeM71Aez/WfLiYQY0JX3H/8Ox0XDh6dxiWJ1VeAkSIAbToBhQ3+b14FGAlJj2TAXcwvpSLtO+TxKTgcNb39wtg7ODJcsKywIcY3ulSSYQQimfb2JwrOpK3EhEzbBPgAALP/TVnhxAZSMGqLqbk7hHtIYo9ReELrv/fsHbPWika3pzO7tw2iOxMBhzenwix0xaQhPtk1/Lae4dKpUjvoeT8rSNcjkSBZMqEnrsLPjA+K3qcJR5Y/ePI9q90wT6rexycn+ceYhMoqZNPrB1Q/lf3DLHhv/otUeUdpv+0OII9GKntRmVUougVNYcKH5X5jgSJcYtw4X6e615yV1FZmrs+IKi4jNn2NoNsuWmy1sgZDqWdSm9x2vCjGbM9v+0dVvWhp+kpaHt/hg4FZuzg/w6EiP2ks+gD9tnLUJpkWhE6dx8qcgTcBdk7WrWYshjvS69fJTG+rtohWfrWYtZCJU6HjdlVU405saPTvFMxLOv9YgwKHcQrY/SHY3UcKYQHauRIgfBlZGH6lSsIJdtk+LYLl1twGpOZdqXUKOuB7Dv9xVvchnY6RHwOarWIQaCfYbOO1QRW5FPyiIBN+Pniqz6UZ3waQMJEfRmnuoTWmI3pFaPap+1NEB7k6YPGAefPhuogFiM0qEmwSuo8a6qXyi/kSeFyccqZYeFJhVB3n5s7OG+lTb1+mtqlEGl7jcZU0uhxsWQwQ3dFQUXXjWf5hUzIB0qNJtE0ccGtrlZukQ7YgL4OD8c6MRwE8qjRVH6O2mkYGSlzG9ers+LWCFAg+CceqxCT+UIBMXuFYkUpmrXrwWSyg6462ppyA4YPEE7W6o5gYe4gH1S6TrM9gvc5RcUkJwIMq5RrUtYHOl6IoZ3PmIn/NibpQ4FlYXfyP0fGspYxalXM20ibEP3KPTbbGIckH0X6cxS+eAMeI59S0UxUlMaG1TLCHF3amCy1qPODsKhPwHdTSj9tslotm2JDCYp3HAidIJzOlzx4mSBJ5xzd17C9vrV1MLoto04SO4KbGy0ybD1W5C8YXje2vyqzzJfeYaTslAuIwjzhiH1hprFyc5uxnB9iEHefpa83K4P122WSJrp7e/cM7SUltB1bjP2AKXhGFnaQ5F2VJehV4iCmmRClpV8a1+3/+pdXqJIhmS4R9i+r4DVRxYfN/5QovAKYq+T0MfoLXHglUnzrvVftXIHlSRydUmGO7F4SDdvwOJZ/EKPemOK30/F+zCUbMfqToqbe167YllN6JnvlLjrRFShANYSjY6diDWJsFy5qIRFCXqC5Yv/exsk+rpFggjNVTTeysxYySq7DZhmWJld+KQoEh4U3ernBY+9NfLKeabIWs7x22R9OQksFKbMGK3yaOyJl6SX2Q3UlGdVDcr9/7LeTZ7M9JeLVg8JbN1g5j2uNg9+qSQ7Ix+aYXbbeVtAEx4oSw8GZKE9CwmlBtno0jz0P0n1WAe7ot4R7fmuzaP6xBQTW2ehPiTH62Q5OpmMGgwlo/O7zcMAwxI59nP5dLimVZtpJvXvZRC6t6jycpk84X+KEPiEYOxeNwJol83rtgWrKvTIFQSawcNZSbJf4tVQAPKojbAKXRF+UBElTxokKhwqXSB807te1UopTcKPgEJ9cy03EHmuXLxZqtPrLMmtLSrNaY9XafE1zIaQzsHu6B4E0Lr1vNIiK2HkoHsxmcwTN8e0ERokG1BGOeo00V/3nXu0t1m4LQ4tuTegAC866thOJVnHbcRTGZ0jOs23RHK7JZz/Pw5kyBaup+z4s9nxftdIt4bogq/djcgVh3nUCYuWnjR6sVMJ9Y4CCCgNW8/AirPx+6eULaAgDsxjobSveRqIzGUMTRUDvaVkgqgY9R0M8EQTfl12rCkYQ+Qaq/J69U74LSBT5KXcBi3Dpc19PolZoquzuM+yBR6n7+7LYxiaYi5SaGdKptUrQrKx1wQJaKJw/Owfy/xfCMCIbXD6yjAb5wy/zbcyDeJJUp2VyjYcPYuj4awaouOZgI+9lq9OL3Du1PFHd5RKOEc6ygU5xhgH6r0Sp0iCBC7vVs5wMFVg9HllY2KzT60n5QXBxkNW14VHeEY7EnRfKu6E4YTyQdsAva4EdSmqyZxhMcLvlhzsThBZuRAJ3pf24a+tqQLs4E7YIEdfImLdIbuJQwVq3+D5TQGL01aLpxTR6C9Njo8vP+2FXj0QIT6n+A/9mgZjgQ1ncfO6/W4bqkRhIUB4em3EEC4tBkKe8LE4y6fVeDAN2d428UVOCsv0twuEzmZNGinm7NnU+YamuLEl3tdyN5JORqRulhoVCR64qLIIgA0nyDMu2Q9cBNwVKxXOgmGaip55+SeVw2KBToZj8Z12O6xt4LxzeB6GpyRW8mENHpknHjrZfARvPmrIlEF9uZHM6yyvCka8DWoCDYrBixSBu8RT9brmTNfzwA1zbXtr6/Unf60KGvpstjXH39hvxGx0NHDAfA7wbcsncqujVZzYd+XFFbI3hv4Qa1KytWvNIm+3l3RPTFr9Ypre6XSgrh6deWK/7zT8u31w30P+NChCVhD3QmkOYqx7n3jK7mmJavOEEsPr7FcX3lZFtJNqhIrG29UtVbSg9ZgSecpOGcYbtLO2CURg7t5B1doM0CTC3mhwhXI6HJDX7R2Z2M29kOmp7jMmCtv1JPnmOEDVNXMXTBaYSpMMPVnecr4raM5chS0aGv8bg3fwJ9Z5428SxAkZH7DAH3GMjN12Adi3xs7T6DSz9DF6G2nd6BC4w0w9irLOITlX4UM4M6YX4ZADwifKaSzbLFQGMc3Ca/0GBFNKrmLfbGlhXJT1u0wpJdEQXxtzKP23rInuT+S1/VChAiijGAzw4fJpaLGTj5MBs0nssOmWjJjBuXdBY/vIsdSyKkLrUBgCrR4CTOORdCV8y4zc4dZq1wbkqOBo5z8yCccmHzJMja31pxoznCpkFHtZxDSVeanWEOiyJILrWC1IOzKI2eZXXj4lp190fRl8GWveLMs3S46VwK25bsZCp0rNCZRL2BE2Q/BYuH4mUayN7D7uBozjcR3iNp1CfpsYgRlHE2jHPeHaFPs9tmmkEjjzmcbT7yyZkYgwHUpTaAO2uPVdM/DQwgg1iO8HcnzMeRKXqAI5ylyvI3T0pgFE8DxZFtTX/F4z5jM4yfFK+BmPz3LoLFJCbWVRUZ88hQgXgYyBJl9fKEeKbIuvtAMaPRKrAlJp/4FTtjwowdYV2lSbnN9X4wcNspZ18xexA4QYLNBOgCl6UTaGbTFogYhnv5ougcphdxMEdNsLvq0YFeZltxpkbNoi48FOvYGHeK9A0jCUs1vHwHSfSYLmE2crBm2X+XiSgwKLmLHenrcEHW9vcmwoNhUZDP6YsfYT32VdNRkzA9njO+yd3om0ZkDp6Ks9HtxFTWGRHOzEGHT8z1feyPFwDB13yiutfMkpthEfXb95+GvVONnebPVrS8GbVVPIykDk6OoFJkSD3T6OaQPyBhU6Cevswg4j91w5eRFM5pA2llSeGKZnNUpUsCXWQj25ElLqk9bsA6ZWjtnYPZFG28ZwUaFDYLU1QPvAR45wuI61GUNvbKtvzPwmPYp6+NDkXW2w/Y96jHsWI5n1SgRvr5tvw7B3fh5gdkYypeDq2uA93WixEsoC6AY8hn/wWNHuXeB7SBTecsaacDoPBn8+HRx1HwZOB1on9KoNVBH8mYwb5G+aUM8ZH3ptO536pq15Futg0l7iKFv94YZdqkufGw/PxsV6Dzl1O2a+eSG/mEyweX9PuYEV8peLuC4mC6txKedwEGfP2TQIBD6hhhSWqywsIH7070o4RIRWlrnJt20Z9+ttqhXms1v3yt/mPEFF8Tl19X0tj8wt/6iepo7XU9QOU3QZjn3CCSxlZIX8qZQCP+Dfl52s0WizQG9EW+tB4FkblpSVFJ+bhq3ZEqe4dyXvf2QAZFpItjQ5yauV0he09FxqOJpkndJEjM2weX2L4vwZ0SRaVjxHv/EEdcsUJwKiiAjNuF38L2t799iryp5Tm91fbzSlLOcPGFcsbk+RT6+45LDpvScxsPY3bOMeP+SssFz3dCETH7ipnG6qJDR24oxLjXrT22qZcK3MgGljVh2dZPVW8Cqkzcb+TS4tl3B9UiW3sFtHJ8jEH3RbNBifPduPvOhIzY52UrGvq/oAAM9DGHunhjzFKxre0MzFrlvtwi0s43dADcM+X9CO8TS14NtxB5NuJu2v7N3SNMukzm0b/bSHziBkfmwd87/dsct63KXvdHieDPYhrfL7dPMOrxOc6OPdDvvEz1ut9lLamaPYCPFeN8a0DKuHZ1F9E2VwM/hFaXY9RPMNNvB/ZHCScnC/RC65UG1yCnb5bxPDsma1W2+CZ51wIAxvpbnJXtUIRxUVi6fvfwUS1omrPSQbOP34AN+rJ65kwL8hNiH0FGNGPAEqE6EsQUvM7lgZIHOhwp1XqRm5vluEBFAiRPCXET/K5ILa4r4PddFObGlN6qjVGGE3oD2brXxpw9VsLhwvI/duBVn6SWTDSmpvqxmTqg9gGgxg3lLfZ7mUgwQlwptCOJg6npty7LZWcNAHbkANwFbXctUpPLypRV17AUHcp3Tn6wGzqRKOpqH8of/HFf8OXMkXzJo+Y7G//2t8vi0d6LAr3WLD7P9ZEoIbJjoLaSYHE3lviXyKKY7acqZnVBEh8437YUO23nLpZ/ZQMhhvv2J/clPT4e1yBpjYaJ7dZOz7aGofOFXvopJeo5yNV/YvqtOHi04UXiMcSc8Vp7KlJ74HgnaxBhWAxBjpawlShkrySTg+iW6NYIPCscdFU4EIBg3PcuGXpKK1HYM5qPpLpo8msWZ4kUePNM3ZFu7rCJrw5ZF9jhzLUphL/rutiENUSJK+B2uY5e2bhZ9R0qlnOGqeCTtg0Doctjyf/x8LXymxr8JJuEBNh+NopsvVVRXyg06QOe0D31j50e4z/YshMUdb0LI58PqCagRa4vaVomlxv+h2TievQKwn94/ODWG7gi36M7cGykSiOi0MD+kqLg/tTMlLXCHX0898R7MRWYHDrAZG1VryyUA2HU9qQnmPP4KQWXtas3+DjIkL6SdLMYTvvG7uizBrq1JEGuYOtHQklMX5rgL34LoKgGfmJjwGcbHDspWPGqNJiKVY5Y+K/YJKdRVJspkFiDM9YLqzXo8Duwa35Ud8Lawr44jEn+8xx7Wic3086GRpW98EgSegSOQpw8lmwnfwaEGd392BUFEpSwNwn7QcbhavpDbzznZ9rWmLq6qzp9JrWlIdnoCUnm2y9I/txjC1961jTqv+/L0CPJ8k8ErIib2CtOWjW2wCWFB58OeLjsmTa/KzGx3MdQ7AVwMdnbetZgju28Pa83nI+P62PPdPpJUWq3ziVDpdK2LfzVex39+SrpNH2Qy5ctys5Cv36VEXKqcjQkFI9TfbiiLHizHeIippI7TytlKt8Yuke4jWBiMHh+pKCwe14MVX0ws054/GnyNj3YWun632EAvsiz0E3hKxMak9LqeEMq2E2GswvrXxcqmlJzvLpkyk3XbianluzpqOAmJG711Ja8qAfbOlEn1GIfpHltWhghBxYKd86tCiywsDYWtQWRg8zBQ15Qzvt3Ba9cCbIoYr+IoVRw3RlsCzk6O1HgzkGmoqV6J0qb4VOobfGkI6rNarRx0MAnFQc/4XRZknO1sCU8bEtBWm3onZZwKziwI3J4qpdca9yFUJQckxF9a8Xu0f0b6+mFH1+AX1d6zfO83HISEicTze0m2MtSLKdEtXFU1xA3znx7x2820BuWgwlL5SOnXxWYs2a8by5pt1FvUYjlqJZD4Zqf3HFNQEnxna/gRnCEja0HBzwzt/VUAwudzR2v9GMKJ0ZyyRGNvk7DfKtn9os5n7xr7muO+7ywfMPl7d++YhlOtM/cyKu/sLw5QMu5b743NaVr89+WvvvHvu/6QYect6/t5zi+eX5Snqt87yjLwdWfQeIXfx6wJeAZi0ezopxsf2/xunNfrz6k38c3Xr1LumQCf0njiO8KX2ifWnef7eylT9/6vL1gqkMezFV9qL8czn8j9zWWuHwUvya81yfsH3S9oyikeyS/w/dQvt5zgbJbH6beYG+6lH4rxF1FZRlCsm69f0f5kNt/qlsPpW6ve8+wAwEssHPrFNxe06v13rtkGH3fvslzgUuvHb/TCr9byu8m70g/RV/IP2KxV40Kq36RezyDX+7cankwJN+tPbO+XyBfl/69QuhvvIxdRmt9K7NEanFEqqs6+Nq99C0CuKwZykFSx7SRMgQpNBmv3xcdjX495Zv/hGKoPkEjiaP9xJRvraHxsMwLVfUV72dFiK/te7LJRok5VBafXEavR+CeCdnYOUbO9lwSKYGrq2dZ7lYufFiI9ISXapZFSem1zbV6IjITgYmjFQwjkd9ZTKwY=
*/