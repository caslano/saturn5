/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_ARGUMENT_HPP
#define BOOST_PHOENIX_CORE_ARGUMENT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////
    //
    //  argument
    //
    //      function for evaluating argument placeholders like: _1
    //
    ////////////////////////////////////////////////////////////////////////////
    
    template <int I>
    struct argument
        //: mpl::int_<I>
    {
        typedef typename mpl::int_<I>::value_type value_type;
        static const value_type value = mpl::int_<I>::value;
        
        bool operator==(argument) const
        {
            return true;
        }
        
        template <int I2>
        bool operator==(argument<I2>) const
        {
            return false;
        }
    };
}}

namespace boost {
    template <int I>
    struct is_placeholder<phoenix::argument<I> >
        : mpl::int_<I>
    {};
}

namespace boost { namespace phoenix
{
    namespace expression
    {
        template <int I>
        struct argument
            : expression::terminal<phoenix::argument<I> >
        {
            typedef typename expression::terminal<phoenix::argument<I> >::type type;
            static const type make()
            {
                type const e = {{{}}};
                return e;
            }
        };
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/core/detail/cpp03/preprocessed/argument.hpp>

#else

#if !defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#include <boost/phoenix/core/detail/argument.hpp>
#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/cpp03/preprocessed/argument_predefined_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#ifdef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#undef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#define BOOST_PHOENIX_NO_PREDEFINED_TERMINALS_RESTORE
#endif

#include <boost/phoenix/core/detail/argument.hpp>

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS_RESTORE
#define BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#undef BOOST_PHOENIX_NO_PREDEFINED_TERIMINALS_RESTORE
#endif

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/cpp03/preprocessed/argument_no_predefined_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#define BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#define BOOST_PHOENIX_NO_PREDEFINED_TERMINALS_RESTORE
#endif

#include <boost/phoenix/core/detail/argument.hpp>

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS_RESTORE
#undef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#undef BOOST_PHOENIX_NO_PREDEFINED_TERIMINALS_RESTORE
#endif

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#endif

}}

#endif

/* argument.hpp
RvKyE0TH+YaG5TjREcMrfzRtVOQliXE70dkGPsHOtDTdbjpkbTeVl5ca82w0lTT8V5Q5oSfDDnx2l7T2XOv2e4Z0kH8gPQ+Cp/cznWvKnM1LSWeo40I08OZoyRsU1yQTHci9I4r3YADKFKsIW180ElG3kPWo5Cb6xKkwWqvVLv4SnzNufcZIQtb9wHgEYLtK4x+4Uo25GbGux6EsrjqSDoXwJKDrAgQcD8VoKwZCpKRRwd+rLRQSebeQ8qiQ2shjN390OlB2BRbv4WkqLvwDSyo+9AGREK/y02N0yuDV2Bn7DYVuGuLSD+s5sDr+syP9t/Sr8QRO2RKaeYLVFvLksXOwiuKagqCKIqBOc6XVGL0vHXuDxdX/fIjVNdRtIUQgP+vLUT1I7PUyLc6FgsgDLisEBSeCEP/j3PwNBr/FrrDWYT9zOhqF5fvWAN+wcIh7kq/uy7fzlKeBTrsSsmT3AcpiVA0zQdZ45C34y5Y5/S2EXSpxADlJc8rl4SdwWFrCH8FPcQlWum0H6G+I+MISV4CjjqeEyx0U0mJifPV4BV1Nia42FDy7wzcQu9neKRWRhvsCufv8KnnYaq19VxY7mLdL4X3e69yZ3pn8lJwe/PPfAhaTtA54SVPfBBMqxIbp5Ect7Q2wHPTDgghu9xMuG1H8ZN4cjKjPB0Li4tHXFYfergZmpVFZfm2I+h0kXJZL1TSStaN3OrzDZpe1sQWY7g/gUpHi11DQ54WuavslvjiIvCc/7Iu27YmWwDugeD9RXGCi1kbsPLPdY+DXeAbX91OuMsbpzuoCuG73B3QPBkLcDoYoV/HxJzaO8ASdYu7GuKZCJKiI8O1oxK+k2nJQ91heOOqVaT4hyNDbvceoWEfAxulG6b4QVPSH8EBTHRM5HIYVRhBbBwTCoY2gjsNR3ehDi32uoV2q+byw1c95erPNx/egjp1bu40XD4DPzWMnb5oIRm2zUGXALeS/LnM3d0qTBwnA9eVkFq9UD2KtkU9+hvUJ/n5zucifglmMsNX0naOSWvSw1Vjh2pS7sMHLH35zIz0Og3axEoXQ8fq9RSp4jL5Jb10cB853WJk+iMMF8Mxg6wuQmr4Nx1dsofjdJNuASu8JyT3x1xZcHqVW2+3zlExikM6ebGKYzj66CtXxfuMQy2PAqAxhzUb7R5LTFgyrZ7Zv0lsfx0HCdV3CiwP59/cAx/6QqAiDWBQghZ4KNLy5IORV0aHapFNpxQNdWue/FS+8nfV+78GQZxxKlipa+C2EOEzGmg/GrhtnLLL2lUYH0oq+EB1perL2kUYHDMvRkFpMHrL2lka227hs+zalFQf0d8auVGcMwsQ7h6UkEvf4j7D7cOLWPuwDUtRact2V8Xr4wUuY2bXBew670LzEZFbLyTxAnPhUG9oNBWEb+Q3tP8d1G+zDqPijdPvqJ+0lXIIka1aJ23Nr6/KuhkMsoCEd+2KcjocDw8XIrX3pZR5og8IxbFFUe+qaiomxoatH1ZujaxGDGuGwwKA0oUFNaY82kNZThM4e98FIDoj9YJBydQuXxSP3diCEJx59C37WO0A4+a0vTXqJfQOFx43TwgFhS1zldqzZKQQmkfZ4P2soEGWX9sRk/9HBwCPCkwyl1h7s5s8/5pYOQfZh/6mzV67Bh2fn7xwhs5IdUinNYBf0jM15E2xLBfvczxMBl/ZoAaSVaEOJvTGyG/fdq+u985R4wrg2VSJD0YDEPJFZQB1oI4b16u5cR+DcB9ylkT+qXY0oV2Jxe6ScHPZL7B2E+kPgqOSfMPIolwGf9EHuuQIOr8Th/Af9x8BvuTTC9LCznkns/GT6967Hvv8LXWqEs7xah5da2DtCGr0zewZZabybQMUkEsFPSR/9BPs0mgo2/4JJVNZR63t+LC+ocbcUQ4a6B2Wke3Bt3MSIsqIfDcjwyOI4aYLh5OObd4lrF+Ql/el5kEealSz4ltyB4F8SE9UMWEIE8Q8H5GREzKYcDsOaEq7R1yQ4QGOu2iEGCYK6vE+YtiJY+lnN/wDGXNVD7BPIdF/41r3+68q9GIR9uI4AbZTN+gzUJ+vD7c0Km0X/S+14gAM+KjY5yxUKh2Sbw7zFlcGEVJUyUXtoBejvbPuKsiSAmbAvxCxv0oD1Qg1OUHSBTsQh3cM3+JT+X4Amkeii3YkkhqHU8k7oDtnWZSYfkrXF/T7YBn2qGADvWRTDi6DixLLHtoGwD4ZV9zkWYi3EBc6HQgZDj3r+EUo4iwQ7QZTUf0auST/Jke7dH+UvwZBRwKpYEPhln8LxsUzRiDsxvWDNW1sK6IJTttxFayP30nGcyhC7OX7MIrXLBQsPfWM/VJa9Ya9U1moj1P/nOsYtmTsHckHZSBByjGRzgspW+XI5QgRsbWjYv72SrFQZIZwYY4B9kGuC1tV/URrBLlAunLxVdNvSiZW/OzJ0Ubo2OWC6GON5YFiZaDkOv6+Z8jsDnW1wHk53rGNAa+xS+Z8u1B7pA9Cn90O6GNk+gX3GoejnPgwZeOFPilErdChkcLO0621IK5iMLNn82kVXAGzvnN8HDTO3E+xN+Kz+eYlugohAEb2ipwM1kNBC2PMg58wcm6EnLmxakqYg8Y58NIBa8Cf2LUybX5Vkyd7x4RmYYAQFX1gmEqTwMpVBpBbq3u+HyZrLpV8kKy1gF8ZowvUXp3UAzwnTPqw28dsO7KniXLmoIGnmbGnu4AMFC2V9G1oNb5jnAV8db2zP8DWbZ6Fkyb5kW67pnlNvV0zSmY4j3XMt4wAEJGc8eizsghMzRe3B5J35e89rP/z++0SE1GBJMRFrZNhtg3Cl8FD3EOWxUfyLg9HW6xSP7h9Zw579ASkZfH1YAelP+Fa0k0RRniVh7UNsurV3hvjshz5sJ/+hOavXquwFDcVqDGbTP4iwbP1iAHGc/aeg+4KvEgMMgdwJ6PLaMDyOFu1JDIXR9ksUw84G82CJ2IVhJLF0wd9QwGxh7NJ0v4imJ/7UKc4FYZ6PIuxJ4HP2NPgBNr/HRPLL15KA5s8fsPRhd7/xvfjyrg4B9p16xy7DSVv7weGwaY91pzTWv9uTA8DSaDtwtdn9HgE6e3gLsWmD39ajUHBUvlt9wueXEUsWHvKhIgUGnkKC+eJo+7BVKM3yX8sekHJhyKXN8gC43hkkQ+A9wjQnQUF4mkRR3RfMBIwG9UGReIIuWN8fByDfVwjTRZBF3+fEYBRGaWSWf3xoH4b3juMiWmowhEqVDKU1kamLRFjCCTQ4lzDChYe/ceJgdzhA75xBDMC+ovJyNLqb/f6XWDHguNjgCUmjZJFFEEM9cSgh2SBfOY3J9NftbwA5+6ECL1PQPRZPv3U42mxoEf4899anSmlalqtvem2goskMjZdP2U5wEG7Z2oU9Muww8H5QxgPxTRAQG8cXk0W/SrmiDVbfgdq1T74ui/dWnxfMsBGVZTRXuM9fjXE7U5lBC4Cb0vurLA4gc9EbdKXXJje25gaP+oCacR84d2Cljh3sDtjZHEhXJf/xGM+noNP+6yG2zNdPBpT1AAxBBWyH5sSnRCpBNDsqegC995Ls7gEXyCQxBmH/RO2B+SZYVd1ZVxCphjYHgGtDDXYk7xKK84gS2DOQwQSGLK6y9QAYugJ/xu1nftJI/LqFLCeNbhfWS33cJtey28dHt7nPfjAaZqgB4xOFAu1JbfflPxXwrgx/jX4WPeWf8dFtc4Y9Jb0JbOceQZ0N4hpeIsTHsysUcWzPOxWiWukz2T/M8ujpE9jLosLdxeilWn/BFATi5VrcfuGN4wX9evlc0ddptF+9hMQaNhtvJfjp0WwKVhCepS3Gd4Rzb2vTktYulK8YA790u789CKUxgl+c/MDiWBfjdtBhl/si2r0fQoWLT3RjXOVohD0+EuJHo+7NekUL1wbaQj75ZBdMWPwrFg4qOXGrD7iuPZMSROiR37gNqjuzeyPEv/kPwRHDOwtVmhCQTDJi0nKvHYg6/rH/dN0QylNLvSds3Ne5p0GFfipR84Yk06e6j0CFBAzLuimJacP4iFkD6QPGfXSLigW3Tk11TfNAXyoSfHZqlTVweHLhRChIAUvoF2qD7WHEvoPZ1EFthOY4XLF8qM4RZK39WdJfa3wnvb+xA6i984r3IKCHHF17R9hseQ5HTiZaLQDuO079AQwg+evePEtMR/raP4hfso7ts7aw9KNCIFuVCPLgQasMe8DXbCldAP8UrX7Xp5VEty20Z6xeEnyFvyZkBxUgyYUg/H6Ncd91ke+rnD0q5C/UhH1he3d6D6S5aEJo0XrRwkO2MVMmXfAKj3P6Xdjc3+cl6f8lMbq3iGBRxu2AyZ7QUISAEWxFwh0ojzmaVBhx1Ktdcr/eAWs9ymKAuZj4uX++0xLFzl9u/FsuXFYEf9LqNcgDO+S5L3Q0PawNIffe64SYDIFz0xIlF24WCjuLAvgsCEaagaGHRSPNFmhjC/q9L4bguC98K8KBB8DVfaGCsJrtxSpcMG3uo3mVc+p/QhgT1dW8o72I0xigwRbKfRskVZw/BeBeURMCMNXBGZ0AhPfEoz0JvxOiR9TZc8B6oyDQVdlPF9olKU9jBvivKzv5MKMu/Xdkb581gQr1aKAiNs8OUhwm687yNLgCn6/MAVZX4V2FLNYzgi9UatCsGGE21D4BAiDPhnLYjiwa0RImQ1AiPph8widhm0hrA5L094liWwd9E8NRyrplNx1wtqRVblXSQUT3BPgnmCj/OON6G/HO7uBruEb/PXSCj+54P2ooAGHP6GAohN6vqNZxPy8c5XlQ9CCFf1BO/7RrUHVf0dMyi7cr7Wo4py7HRU7HkPW8P4TPfk5ERfFF+DyNe2DY3gl167OO9G+me5geRVSASPTu7FYfzt4jFVbrgFNiIIoQFRo+0c6BZwgKGjRfcWhfy2eKUBAv1juLL0hqMGvHbGbPre3K5+3LbKgiJsYOjAHFNQDjPd3lQJT3AHaDBRwwCrYUqBEuFlxnPS44xrwnxxf+YK/l+RfKFYrlu1/eCHsUogGsug+EtkOc+y2iM3Bdn2t4J9L/VTOLcMehENjR9pZfc2Hl4Ej+Q890r8BnXkBu/D+uGkdXfTFivXdY1PwXAeiPgqrNFW7Rl8GujevKfQ+jkJ2vJrmFWC3JDFR9pECPO7UQRJ7hM6iMdODsyk2WIwQQVwyRgihUQjQGd6n+pBC796eOazeTPw88syz8PXMmcAeY/lUf3g8C/UhUp973AdVHNTPgAkNcaaonhrYd1BvU12+/v4yhXviv9jVaWKXgxwVtnv5Ro9VHsn8ltB2d3Mu4r4DNhYOYfsKn+dCtRD/0cICIVXMM3XYh4XA0M+Dhn8R/FcS4obJsQ3lj1k6JRYlL/G/LoVmdmcpNEHZHYcIB4erbMYD2l55Y7/4AvjTuDlora8kuSBbgi3edyN+Xl8SyTiv48zNgnkvb9ZFjI8SiP8gUE//jBv/h/ueM6ssM8sa/3EVa5ehpq0sy3RtAcW6aCKQdMGJsZiDmGcAIR9NQP8GmHxbYW25vQmkVJXc8ABttMVT/HakGER4MdO7hVjZPBFkMbA/xKOtXWi83Cb7B8fQjhJPXBprcW7KSwfIkfNJHhkp43ooCIETVF0km/e4yvU1YLF2ilYEAeO9QVFnSvaXP1Sqnd/w43El0WyijeBw3AFTv8KGDZRCj8dCydnVHENXBMQiTfR/WYTAmmtouqBbrX/lJ+zrfCoAR/MF0OuEF8+ZG6hMl1W+AzXjjT6by7TFAanXxFLAFX80/WqqGLgij74DjE5W192D8hqkYIlGM0irujOQTghK2mUHsxNQWRjLUuZ8Zo80VrNHXlmUJprpAmpRmYHHB5mTR7cp4O8Rre1Q/YdNHyjHTXmYx24tpVUbYQpfamtHcmwepcgQjFByzvM2VYzh6hqib7dMAEBz3jkF6KgEYfTcGjqi6L3AVIxiDx+6ctSCbF8aDfoT99s1znC1E2u3BLuywzTHfLSTWzjRHkThrxK5Yqn31tpDiveO6kOJ9/Zf/ZEZhQYjjgor6rc7b/06ZsD1iTiAyzTPTK9C/PKez7Q/BWHVgObQ726xQ83LcvyzGB4Zo498Trg4+uj5Q2AX1UrwBclcv2u0S/ugCUnQqjf/x+0CCW/S1rii3ff21nR85ZgLesWsguxcK+hRIX6DkRQQK8D/hrs/oHmfiurz/KtshvQPxeSoHW08G/yGSgzftaeYSjr7EwUyZXV0q1Z4drwWGMyrPoFRHOg4AzUVklkt1oi8Rn8B9Cwm2mAgYItdJ6C54Tv0k492G3yPHfxvksDC5hPM8aIAAENRH2/0P4XZIow29S1Zkwnev+mdeX3bYpX6RvSPxP+/vL4PiqGCAwaxJVIKf8s6NZvb0QJSJsRh9OFQ4Gn5mqDJ4ZO/ErpfLfwUFMdC9gu7R4gK77W91/VEuMTgUHXi2HMJ9U9/6rEUKZwACgi9IrrlVGLe5s//2WNr3K7rRHCboLvI9iMAk5nmQdND17//h4h5jRGe+BoCv7d27xl3btm3btm3btm3vXdu2bdv47/N+fJv+kkmmmWmnyZxzPrTYtQHApWdJ4Gg04fPlADmgzIROFfArAywO6C99QfEcxT18ePuORL/FS2iBMwU0Gi5GtSLz699OjygZ5z31W5n5SNVejNKLpPa4N2BNcYLrQMHfBOAZy2k8ALo0J19xyY3Cy6VKxnlfu44hhONAAO1sIPgka+zgjs2MMLDNbtstO0LisJmjM3lw3/j2s7EM2IY7857oN57F23MYDxXuISkEmfZpD8Z47l6Gcyj7m/ZbL5SB6wBak2SvR6oOtI76dMKTkF4s8nOB8oiC3dm8mmXIYNAYfA8sHJ8rQeGCKp6Mm8Y94df8XXOD64xVsyf1ykLZxbHbn2FjsQlCVQiHjhT/YxMaXQT20osWjgXfS3jGcTQEvjcJGoWTA5QaD5ADq0vc5Qaf9eR4jJADNkJdxFtqB2cilyrMYTwcrEhrarMrbsdMnknww514N2N0PXayWjtfrpvYBL/aIlRK8zd5xI2rM+UQRl71Fe5s6UwQm8ili2dQMrXBO41n0AuJWQtv/798iYd/0fwd4UcCyV4/zmnclzG0sAEdTcsNMDxyPpQt1mi/H1shGJo1/hzxHcE17i+NFTEG4RO+CyL4N8ElaXGbnCus83Dh7huRH/RJXJS8BzOejuxkmx1jea9tIDwyOI0V6bVZ1zvtqqDFLeuu/u9IojSGXCIPHmDTJCpabrDmI8GsSF/o3mGaYkg0XmFGe/0qCiHQlqmMYPt01JnsftCp8RULT/jbAgoj91kQxrCvp/bvCMawx+jbhNDG2keY29AQxluLuFpkF7kidxz8ZJYZJrsC6pZNMGjj73mh9vlVS+ljju1yy/uX8SeuZJYCFDmswQ2o2YEnhPlVlGhTzWJs+qCxQ8bW7OqUNDho4xx2ym1yy27Qv2OkWv9u1oFGdtbxzWtGU8yMNEnM01kOX/9YOm1S4h21yCwNcJIe7tZvMVXBpkH3VBLCOfNTlZ7PkuBdEim4AMDFYHGD5tijOG38lAcjO/T6nbVMDx+e6/wenxyp/TrEerxsMLpFA9wQZLpzWkZNM/V55O/ZjdoihcZO0vcuiEz8vPtWk5tgWfutEvw09ZnFE2Yi+3USCI70q5Lf8I/0WcRT7+syjCTcVyUbiriipo6wE+/pMg/F3dWkI4q4pNSGfGLkTFdlLtt0W6pLZO2gN0U87Eg3RZ8PANmoYr9HYO0AMeLu7bDYqY72eBiIjoynxrymI/nHB0CJNHiAwVrj0TchX+LZuABCq/N9FHBp/oor4NoQkivgXhOaK+DCdfh7SLq3+f1O3xZtJO7eFnso5s5W5ccTf28HSJ7wO279b3dskrg7OtGcoP7wn3nZkTNNMxLtkYGmhN47uhuSrnt1wlNC75EBmDipap7BPct0x3t1UDeMcJ/Mr14s8ahPbTCvpME9mlVBmPv0Z2eukwSHt05sK/zkNvhu8Qqwo8ZTrp5En5gN4FBbvWnLnw/LkK/XJ987HxbSGwM9iJ+pasHvbxbm/RvzJ9KbinzIHcpbz42jbXBQ3jrta8/D1237/o3se9N2786chFjX7Cyw8FGJK1Ze1VOF124pamXKt24+6j7U8srF5M/OsBvekSPL2O+FWqMeroFKtehry+mv97b3m63cfN1lByNfF2XsdtYL2MtquT/lXs+dOtXyWGSNrErDRQqjxfg1UNX02eXDjd48xsvkmePFnyYWiROyb3s9NyGVZ/HFVuSHEKCPFUk0JU1eM8aa+CSRypMKhKsr5YaliUi4lM4NwkkJngw65cflwbo7iirdPgKcPe6XDAqThT3uUgw/JfIX5hYk6X1pIamaWYgcJU0LuB5Rm9UtZAWgvE5VoovGXCSJOzsIFNRX9XM25WewTbO47bmHrq0YysjpffZHO0P4icXvUT/1sSV7D2wiiJ8musT5uUW+RdOsD9y0XqzIyegZyjuL1JSLI+6fnXColVjKr2DzvIqF5K5LY96oOVYv5d+aP7YbvNH2Y4e5HG+sZw0OtZcHx7Nix4070fneh95brfcfsJ+d8SzrPcysMleeiB/Z5f0vZpl/MEdseY87Ct9uhhm0cosfMx5N9cuE45/E4b981MvwunkHjmxfn/IxNLEzRog/eV40H2yCtktlJ6jJx3RbK8wa6520594T1u6wIldmKNS143poWg/3nYMrI1mTrNQMe9yeQpwbHSSXpTvY2bfbaFy99zI+ExQvNCdjZHNMInITTWi31ZDaRT98HWUZ3aXEv8+jh4KfpxznIx5s10d5Hh6ohoJZ0VCPduJ0kert+clBj64V0t9YT9AwIg8/Ll83E4QvbLftDH3sO+0N9d3IR9fuLB0iJe7Xnh59H3ZHd4RwLd9ZndO/nRWPi47WrYSDKwVd5750zVZKbjmgJB+uXP5JfmY1ORNT9jRaq+RU222XbO5/3tqYevcMXr4CdWyxWL4/JoJnPj/1ldjXnUmi0WbwDBi1G73f2/JSfStx/7zgcocOn5RK/8D/KQnsXuk+Q/wi4s3OUnKkSnE/O4us0UrL9lbw+Xz7mZpp0DEL3bQtzm/qm5Ob27Uqs7FjdsP0gsWB/Q6pCeETtBXUFfQVrNOv42cWYcbENMSKjg6PLhleFHE0FCkspu+YW1ebNbOksnZiUmE=
*/