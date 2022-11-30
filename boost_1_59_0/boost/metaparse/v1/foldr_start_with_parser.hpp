#ifndef BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class BackwardOp>
      struct foldr_start_with_parser
      {
      private:
        template <class Res, class Rem>
        struct apply_unchecked1 :
          accept<
            typename BackwardOp::template apply<
              typename get_result<Rem>::type,
              typename get_result<Res>::type
            >::type,
            typename get_remaining<Rem>::type,
            typename get_position<Rem>::type
          >
        {};

        template <class Res>
        struct apply_unchecked;
      public:
        typedef foldr_start_with_parser type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      private:
        template <class Res>
        struct apply_unchecked
        {
        private:
          typedef
            typename foldr_start_with_parser::template apply<
              typename get_remaining<Res>::type,
              typename get_position<Res>::type
            >
            parsed_remaining;
        public:
          typedef
            typename boost::mpl::eval_if<
              typename is_error<parsed_remaining>::type,
              parsed_remaining,
              apply_unchecked1<Res, parsed_remaining>
            >::type
            type;
        };
      };
    }
  }
}

#endif


/* foldr_start_with_parser.hpp
x+4B/nVZjWMVj9bLnRzLwE0K0qVxJamdmQSt3G6+wGOtUr7MAhFk+H+Q5IXE1gBLBdYKE+AqrBe7KM5BhumXgX5y7Pjx0v3VUUtEYuqOFP/pdQ+4zQXgiguaht7fJnvUMrtuWkryHrQoay0+G0Yt/BwIuwKhKgOVQhNqwjQFZ+KTVGIhNzoe8mg8RApJ89MnE7qiiZboBoKhATLUDGpWs1bS957R1fAX0KFsNZ/RdYQtDVNU7Y6iXgwXTggFW7vUwCR2LqoDDmP1CH7iB+1XCr9fgUFOn49hm4kRmXo0WLEd+3dLoiOj9MfvjVYhKJMgzfnMhaNtE9mpBQE41KNRzAQ9lphfq4aEf6+baNHRn7nhKSIX9uRgR/Sy0ZtqgQ0e/0ymOo29yjWXxiyDWKjO7+jrnP/noD8cN6VJGKw9UXgH47kQH+RTU4v+MMQUo/3wTmsz3WZxJPnmDxD7FYjzb9t/1hs4VWpi+FeylghiyOfmOOuxtoNbZ8OrH06jzLWipEScbmjbd+LN30wb0P1GC+GCqzqO3mvApwHV1fSoP0kdesX49/63Do2uwv7+4l41d4zrs/9cuSfqXv19jl4xdfs+rDqZoWbodBrYYnqgeKGteFf37fT4ILHFEUzVOqNwTRAPUPqlxBQD9d4lrb7aNtOstvWsWYxwwmChvkBfn1Tew+iyW3wuO9BF9x6HaHAQuoXnyt0f57EzhhTI3aNd2tuE1OR7iTSJgwNsV9Hx+M0WFRQr+posBoyYbRCkvJCy4ioEG7WWdmjJaptypN7X2MA4UBClLa8xg6aVAKcx2BC5U7pFgPtmL7JSxB7EwFX9O2bqYIj99CLsaQO9L1wgx4SItjjl7ikgNEO4CM2I2ej+CmTYpko3LBC80crlA9dyYqAP/LGRs3UaxuUIVIQJfeVCajNWm16Ty5rxBxJD0AXS3BHi1WrYBhUJnVqfd4qqHIvgthe8zXdTsGpgOCFyTASFWkf3wvmlIomlxQ7x5Ox8gjZxZ8l9UU+Gu9DfhZ4OaRMc3I3oQyWDIcFx1Gg9pk+r9Ea8ZiY/7VwKF+kqIQfXm4Q2QfY4SYiBxAKUt9S8D+HUmyzq4+lryRgYNk9QV+YbXZaklQh9+KqVNFD79vO3IvCRuobuQ1ozWLjaDNuy2xl76es/yx6D1g4UuUAPXlWMbEnlp68HAhUBCN5DLXIPlYCDJKYY7xytYbNmTnL83txUe0Du2Bx9DxIO2JGGzTl4Vhr3ERubLqoZVqn3RvFSx/vyknZ6rlCsdR617GLpe8iqidHZT9jVu3nqQAHxKeF8QSSBZazt8v/QclXSFr2q0oKzcjywqdg/GPDp/d4HPCzJlbojy1ngcY4GQLaMI9K5EzyjsdIGbjluZ1sCwMd/rg8nyTN+LFaBedYZo4cITVKoiZfo/NguKGHjwpL8OGWk5Oex/QygB/iIrsQlzkjnFbD4rRpLsQVUtNqsvZ4KHVGHzo07of+7M3t/l3POZwJcv0hFsI++4TKfIeH1Zjh8pHlBS9oC47npU/RtPRpnrrj2KuhGD5afxGpoa1mnPk/Wy98XrpfRFaedjXTuQuOp7rnqeyUqhmSFtvrKFlIEW4FwG4hShBiCdPwcyclDrH4Q2rlnWAMHr2j9z6FY1oqkeHwVjRQ1ZiX3YbGusmxH6oVDIo2qidsihanfY0bQ7xsPvLea7J8LfGjEeB3FqJGWqh/Nf8cu5BqKUBcusYhwcT9OiBlPmxZcHU87LXW7qM25kOTyHvOxjhM1WxP4PQrKBuMt1ZfzA3vZrnE3o/DFJbw9+mfqupYCum8rsumYhMWWMgV5eZpIn8AQW1waW9usbSdUMXYVG5qL2421eWVl6pO1PR4VDMyk5r39TzQE/aWnKbIRAMPeDRRII8TZr5Ib5ivpW9fkY0f8N/z0TgjYw1tG+2momF2gLNfrOEUn8sVkWNkvNqizj+lM6dAbcVDIU6T1LLiJMvfYEU36/hQzBX51Ew5PIJO1ef+U3brj7hU6DUcROhZb57Pvhl+uMhZ2Pa45mdIgLJ0BZKBz4OYriSbzfm16dSaC/2tGQnMRjCvYO48tzGGTVsFp/njMm1K42NDWmq7RIubE8kwZ+hb2yuZabfvokDI+KYZmn0tRUn4tOQ0cx2iCW8t+6QnSThsuRGvuRDvaKyJIPy+MHDFPf137loB+ncXU3bonkfiYIGt8GtlBKZNc1042YGsmUZKmQJ8GLxjka3KNyUAPXIEE8BTQ/HUu0cqOrdtzMQWRkOVIVsI4sSPLj4jpuWjxxmMxIN/fJYuzpJRnk469WjmUimJpcUyQrwMUGX4YdooH6kCNyg5TugZgm87T7XxrgBvYuqNYm8ZIiia98AA9EiTcQ5iuwE0HE3j/yEAwdTqi+vAkgyXWTarfzNiV4/QOw0k1KpMHUXpz8hKbkJ34dGLbj5UktDS8UYroKoingEHw3FAGGJDT5QLLTvMQph5XlheEeBPJ7nwA48qbtd/onfF3ntLjLc8Vj57uB3DSSutQ4ZPOv66xZy1drIxrvVYma6LrAnucC4EzAimASBBKNJlqRyu7oFjxfJrgsvWbrq+063sS1gmd2WvReLUDuhaHrPwHxS4Xmg21+3mMpuuh/f0UcqSt84nTgjPsxhwe8ItKLLDkesF1/pJl4uqVJiHlIJf705O+pL/ShI5Pb/MJQ9FMIdioI44AKFBUYbSqiyUD0Ed46nFsQyIUzfQmMnRkDSFfCgVLwJV0nQ6FzYI0IrqjoUOEzNdZArck0WWaSk5Am9sNSW3PBlEgz7GWBGoyZJ5YJC9jtW84vCJjyT5rEFXE3m9HcgvfmbbWv35I0w7TE1WTW4IUVNWGYMQo76SdlkQoKWUpVkLJ3IXbnfWyPvI9QWbmgBTeQoQwSPDKXjMWm9oyeLkU4swWIh6/UCKXHB+CJ/qBDnP5/BgE23qrHJQ+cNLn7bgZrWGKv93l54xC4avk00l9rY47vrvqy9D3/kBsbqYcvhv6iPlJRh3Ntm8LQioRgNMKu8/6ktTjgStgpnYJpjmgQx/TAUHjDEyP7ncDsVvzo07g8FCG9l79NPeQYOAEqkFa89C0SelzUn0Ot0d+hTSxJCvjanTE9Y2efcMDJdKEUw1MlUkYetxIc4hMQqDCgaFyb/7IfDTFP4cd6P/x7VWQjqzYAVb+UU0smXhmVk6C5xien7cUGgvWnDPBsae/3gu4Bdr9hBg6OKOJ1x6f42tnUM19+JBgVtfgwUaq6yKLBEFJjr/mxziOrGvMjGHvfc3V0rrt3uCqZezqS9VYRQp7PRZ/AavpzVJq2SZda2MQzM9aXBwioblV+e/fakaz5FlVZRUiyRQOzD8J12yVJyX3Pv8LIzMjNevkllSSyTwa7GvCnJjTm1KFWH1d1WuCapw+T8v72mQ8FI8Ur+0r9eemnJN61/U7vKl5o2g4gNvqaKP2blpNaVU08vE5h5wBEu80GVh1GJ3Pry0Wl9mIoi69Ni51t7ebcB8Ds47CSkJPrUwh0UrdwpIo6Jn0Uh417VIVjVaOOMGziLvMHUvq+TzvOB9brgIfz/UdzOx0J/5JLTjfCobY2FibbXl0pYh/yTD5xGn/3NW1i49dh+6P3lgZh+y4O8GlTck9TvRFWKRG54yoy/GqssT1sf8bijvnk5BaCNlBJ5BOopivS4HBXsTQCmaOto4wtDGHt/RzcGj7EViBz2BrBWt0X/hkhG86BLCU5WJ9hgVFjxak6Ui1o4WTTFkQDYdyWySC9gJhD/dRZkVvOyFUY5zT1kSBX3QWdHzw//hKYI4GW8WssiqAhrTUHXbGfcnxUUtw3sHxWtDHb5PBHt5l7ofFuGivHrDu58/PBCzoQ/Rw6fRiRh/MQ400W3q2sQjHrRCC3hAFCe3bQvhyo3JU6IcXChFiavSCziIzRuxWqECI7JbRrC9b9cfREIUoLpOqRBEDc+MYQphyBiT5TgZ4OeWCInKDUoKLy7GBCtyEoAtqQDH39EllbFf19L5pAL2T6eZdLk3HyCwPF9Lt5U5HSaxpFn+YREVWikdZNHpUQHUYWX2aUy1Uq7iHzwfmmWf9N5F9frkESjMoG2ZdxxmnYANiaeNeRhyymWFw2PiyzZMDniO9BuNuHLni6a23g9SNE9WCOOGkK1CHzR4WStLsA833QzLGOWWkO8+OOmTdc7FjE7D2Awj9RiZQRUyiK++NpQv0Zfx7dg2WSt6TQQASUZNNGh43TLkU9CNDBjPDPcMoLJntkNrrmrdBDQQhLpLT8SKKZAKUGRI48dCXBbgKLn4Szw9tg/gqrLB6dGryayZLQdCMbmGLicuFY+4bZ19nRwEUVQ23Z+lPztmVShK6w4R6vJ2GpKUNEKA14AoBHWvOKHFLN52vbvKJtJUKDj6WTkK0wlskV4R9k5KFP5yrUb9hujo6tj6qpXyrZrgiFT/OtgxmCHmksQASB234CuPOAtnwbt2d1iwYT5eVQakYkCXk0FyZguh1CQYAQEoISlI63XhBsSmOhXx4Hd3GGhI+05V+5n7PEhemFFexKUQE2cRypZ3ZBJQV8QAy/IGTC1b+7TrpX8+CbylB5Ue2zqmceh9giXz12/y45Tpx8CHG1d56jNF/+xb9L8Im5yMdNQtWISYRzA0gJVj6+5LFEaT/q4b8Ktw/mTdtrccrM0YNBZWjrwgEFSsF49o7CkwBoVTrJg85SQ6WOHnzbhJqUcZkztBOHKviGN1Lj2U7RTnuqsarbbVqZmcoG3zoNXLCeoRBp5lJq8qENFp2XU1twFUqS14G5VddgIQfkt+Vs75b8xxnZEdy6tRDKQEZTonrFiIkzOKzhZ2AoQwbhFz/BruWlQi0Z/72Fh/olevBvQk4XIjquVNSN5uUbDDHTt9wVEOehVf3RhV140fWh5go6PTbJ3yF6jIeUib2GY/wIihvPAWp9b9sFLC8IFQIhsHp2hlN16hk+1BoUX0n7kFH6uC5kdbyaXvhZedjmUofjrOE9oJwG7Y5Ufy5DcbipNLILusshwZVJCZqSrYtzBvbAZRiGb5OkMWfJdQAKR+htAva2ME5lsvbwCRIpY2LshBPPM1dReIZbYunV3Ap3v25oJfQ3R9AE8GhyKcLTJb29mUd/BlVB37tFi8j4uwCgq77dsjc5dvU+UhUnINGkLtpav3t4P1hhymLW1pR+EDjQcWR0atZ/7b/QrsDhOACJrIEXxBt230WNUaN78iUYolFuwO6B2jHjRfILfDKAiyczXzbFroBAM/tNWUnY5EDA1sao8lc0jM5s313C4GYW8/OizFcikPUnoizlT7VBedZwWQccZCUyWj1vM6J3EGCithgDgKZsbxwDF+pvifTZkQxsyvx+KqbVr68F7Q7ljEshEpT1D58froBE4CP1tBZqu9sHOqj5pfDhvKpOSNLPFRy0CHTp6rxh/OL2qgdC6cXuqiAMr+H2bCHrZbPHUBy/xmI+ieOzerBwAa7ZAx+kaH9qxB/6Z2MxpwAOMw9h1BUANIfzSra+QeMvXqQ2mRptUfwtJ1n1e9hreZZIpkHt6au3qMz/l955jp0MsajmMmBBPOny4njroXbZ7IjRUeKKC4FgO5p2vPe0di/HHrDKlaJtKlPVRM9NpiSs1TSMQFvy8TICVmr6j2Evd0pkKXyB6Yc5ysQ0OCyd6OoTZgiFLrw8fbNfMT/knFQ1MdfZR+7v8QZMs84jLEIYX/6VLPmCkEEUAiwCSgrhzu8b9pxkLVpYvDxnsM51jLo/1P/anaoVXkYmas8yGZFmntGOACutl4ec+FBRm4e8jS0kaDNIXV33LGJ8vThHveLuK/HrMO/Uqt2M5nsu3PrYvIDEH1PTGPDGevXDcxOdr46TyxarRHQC6BnkNACalEeAhN9ibZQLCRhIai1IiN9lSzIPSqVQyAwW9PaCDEUYN2qUUiYkAPloZDFjnU7UgiR39UzYLDSXsNC9bMb6kCIjoWr7pVksSTgzIhgwmd42ZLh/+9ozHTA9KiStn3SSC8S6Z5a4GWMRDs5sJ0fgqUVj1Ufw5Y7/9pATzaGyD1iDWQMYQIWYSjVB6JJOy1L/OLHcAv0aseEvevpLmIjPi7NLcgMPFjfif17OM1cU82mI0rLx4s7xvo3EzfqZAkdghBSO+Sggf5lTj+SkBAtJ+PcRfoMOEOgMO25Aaoe1TM3IBIkA/jr0uYmO3NdultQVl760BOtbyimkaqjs8iI2wKJIZMaSUrVz1Q/lps2+7V+h/YpqVB462oTjvGZFdPfxEtmi5pi/OAVZk5A+BX90T8uF2hz4anSB8oIIYPbqdxCepUx2BLIK0v96AqbDpU+ii5r+3ao2hxcwlsJV81Z7fL6zQQcRkr9e4mC1lFk0y7ufmkqGzFrhShj5JiWS7gK6wcJQNT467SJH4/EPzeFsrlZZP9AVllI4x45WdVTBhxykPsi78SuQuzmmue5be0bixfdeCJZ5vFerqDW+mSJba79NgXwiFlcrhC2+/jlDKIyYfemODElugXW26iqMlUNckfKJrusoWbwp4P2I8iz3mWEapAnAsclFcjPtjye0hacNNCMX17zBTHNnfGIHv/twZ6lE/EqsbvuivB+KyzeNTBSCsZPIqb9HA+YUASy36ZZWEICjsTudMhRG1Uj5Upn+tYdkp91IjlH+nZuG5lFctEv67Zb1NYxJ7XpYA097WVvucz9M//ROzca97fPt7+UG8kVPz8RC8VdDxiKuCwlCknl2XHa2bJ++KMuvGxmqSVQPtxbVmgotkuYXxUoU3bUNwY58jpd86BbzvhREhnZbLL/0cjde6reFmAnWdZncnSQvfDIYy0smnuQCfoW6CRGhzaWtmt0HFgNOlvRu3p5aPTpcUpIAAlfhg36Q1VmQHG2U15o6zZpZkNt4Az+NZ7EEiao9hwL03Xr3zgU0xFpPVP93XJ+zfSIcofJNT2YptZqYjfE411imadIHQS1dXkC90qZB8kQgGdI/HoIDLJKmhIL9/5Fu4HR7oQ6CDtOn6R5qhxs9wQwAG7ai3hJV2sX6d5Z046DLYMdsBv0JXivmHVBRcJn/nm8fXJynWa0mkW9DwwmfjjZ48N8mVmosoTkAQAA/KI8sLUVPm6stZ6tF4z8hJRqHe56EuIN01Ux/oyVDOjBFhE8JnNIiflTqaFSEM4vFKhkFMrJJFD6lctCZlAgZsmlMdXUcdwtCuSAi8p/q0tnFDUFkkLpeByUmXdiKizHo7HGdXsswWuqidL365sLRjnIXnOrOo09azEMocHM+65UUJJb8P/ygvyD6x0z+BIAmGcMTzvZm6fve1wMDmo71N8tlNZ4BX3iV11ZS8Z5+SHRCVpZ1//t02zXEqVvzDi9W+NLIWsdGG+ljUro9CeRKcbBVFAaKfJrKQWmjRb0twTVgs1UtUK3BJSnoRb0LGT9l/3M2M+tkCZfzta96Xu/SiQh6wLB/QxDVsTkQCZFpESJnlVaqVmjy0AOCiyS0LJ5tN2aSVDbdNa9zcEcNOMVJxbH7rXsWIzJuNUdn8NWgmZCR3p0zUxYJCUHd736H5WNENVUAdZCWbuYnusRe8pQzgRwSkAFVHfqBeRSICxndap//UDJdEsjEd+bSZGuB/kGh8sMwUK/bNkcl8LXWAf0
*/