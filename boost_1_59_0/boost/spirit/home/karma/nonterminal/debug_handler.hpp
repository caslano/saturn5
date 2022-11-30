//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DEBUG_HANDLER_APR_21_2010_0148PM)
#define BOOST_SPIRIT_KARMA_DEBUG_HANDLER_APR_21_2010_0148PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/karma/nonterminal/rule.hpp>
#include <boost/spirit/home/karma/nonterminal/debug_handler_state.hpp>
#include <boost/function.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/out.hpp>
#include <iostream>

namespace boost { namespace spirit { namespace karma
{
    template <
        typename OutputIterator, typename Context, typename Delimiter
      , typename Properties, typename F>
    struct debug_handler
    {
        typedef detail::output_iterator<OutputIterator, Properties> 
            output_iterator;
        typedef detail::enable_buffering<output_iterator> buffer_type;

        typedef function<bool(output_iterator&, Context&, Delimiter const&)>
            function_type;

        debug_handler(function_type subject, F f, std::string const& rule_name)
          : subject(subject)
          , f(f)
          , rule_name(rule_name)
        {}

        bool operator()(output_iterator& sink, Context& context
          , Delimiter const& delim) const
        {
            buffer_type buffer(sink);
            bool r = false;

            f (sink, context, pre_generate, rule_name, buffer);
            {
                detail::disable_counting<output_iterator> nocount(sink);
                r = subject(sink, context, delim);
            }

            if (r) 
            {
                f (sink, context, successful_generate, rule_name, buffer);
                buffer.buffer_copy();
                return true;
            }
            f (sink, context, failed_generate, rule_name, buffer);
            return false;
        }

        function_type subject;
        F f;
        std::string rule_name;
    };

    template <typename OutputIterator
      , typename T1, typename T2, typename T3, typename T4, typename F>
    void debug(rule<OutputIterator, T1, T2, T3, T4>& r, F f)
    {
        typedef rule<OutputIterator, T1, T2, T3, T4> rule_type;

        typedef
            debug_handler<
                OutputIterator
              , typename rule_type::context_type
              , typename rule_type::delimiter_type
              , typename rule_type::properties
              , F>
        debug_handler;
        r.f = debug_handler(r.f, f, r.name());
    }

    struct simple_trace;

    namespace detail 
    {
        // This class provides an extra level of indirection through a
        // template to produce the simple_trace type. This way, the use
        // of simple_trace below is hidden behind a dependent type, so
        // that compilers eagerly type-checking template definitions
        // won't complain that simple_trace is incomplete.
        template<typename T>
        struct get_simple_trace 
        {
            typedef simple_trace type;
        };
    }

    template <typename OutputIterator
      , typename T1, typename T2, typename T3, typename T4>
    void debug(rule<OutputIterator, T1, T2, T3, T4>& r)
    {
        typedef rule<OutputIterator, T1, T2, T3, T4> rule_type;

        typedef
            debug_handler<
                OutputIterator
              , typename rule_type::context_type
              , typename rule_type::delimiter_type
              , typename rule_type::properties
              , simple_trace>
        debug_handler;
        typedef typename karma::detail::get_simple_trace<OutputIterator>::type 
          trace;
        r.f = debug_handler(r.f, trace(), r.name());
    }

}}}

///////////////////////////////////////////////////////////////////////////////
//  Utility macro for easy enabling of rule and grammar debugging
#if !defined(BOOST_SPIRIT_DEBUG_NODE)
  #if defined(BOOST_SPIRIT_KARMA_DEBUG)
    #define BOOST_SPIRIT_DEBUG_NODE(r)  r.name(#r); debug(r)
  #else
    #define BOOST_SPIRIT_DEBUG_NODE(r)  r.name(#r);
  #endif
#endif

#endif

/* debug_handler.hpp
caDFm3IKPKm3BnHxQc5wXM3z3PYMbvu49NP8aPtRbxf3TL2Pn6DAizfdhFOZa/Tc9mL9MMEWFmyAYMMwwd8babARgo0QzEUFhwz2LoyyD6LIa0yOe038eohqgqimYSBtZZBiIDhmmOAaFhwLwbHDBN/JguMgOO48eNxI8TA77jVTPMwQ1TwMpAkMUjwExw8TjJOIEJwAwQnDBB9nwYkQnHgePN4xIB4Wx70WiocFolqGgfR7BikJgpOGCeZZ8AgIHjFMcCEL5iCYOw8e11A8rI57rYhHsRWiW4eBlMggjYQoI4cJPqmnwaMgeNQwwR+y4NEQPPo8eKAxHXmNzXGvjdLDBlFtw0ASGaRkCE4eJngVCx4DwWOGCXay4LEQPPY8eFxE8Uhx3JtC8UiBqCnDQOrVUUjjIHi47nSMBY+H4PHDBO9iwRMgeMJ58PgvZG1rJjrunch7IOpEiDpxSFTQeDZA0CQImnRu0HIIugCCLjg3aA4ETYagycPmLVxkrDPuSz/jOMOJDaBmGxuNH4vKZO6hF6BPKGm7rrnGapUbgk9iR3K1O/Lb+bu47T9x2/Pb038CcAcRXJ2PH4U5fQo5fQ1BX58b9B4EfQNB35wb9BwEfQtB3w4JUvF7QHYRRz7hBZYtgVijBwHgqIF8ABKE4OAwwVks+DsI/m6Y4AtYcAiCQ8OiAPWPs2+uk478kxoaJ4cB9K9+Cuh7CP5+mODtLPgHCP5hmOA/suAfIfjH86DBUzQ6HPkdGhodwwBaxACdguBTwwRfxYIx9U/DBFtZ8GkIPn0eNL7HQ9+uTkd+J3aa/E6I3jkMpAZ6WGTNzxDl52GC/8qCuyC4a5jgWhbcDcHd58HjTopH2JEf1sgRHgbQDQxQDwT3DBOcyoLPQPCZYYL1LLgXgnvPg8bnfYhGnyO/j/8VQ6MvOuYSAHRQuBaAnIWgs+cGAV9Y0w9B/dHZ0yDeJNeFIDgbUFigpAcgZbPXzz0T8M2Lp0Y5QOiC32XBP1mwd37lyP9Ko8RXw5RlRh8tS7vaeYcGj2HBWgceGtzdS4OH68QaJQ6jKX3Xt478bzU0vh0G0N8ZIHKezvwoCz5fZ17DgrXOPBwaeRSNkCM/pKERGgbQZQzQyfN0ZjMLPl9nDp4Z1JmHQ6MBjQq7fnTk/6ih8eMwgJ5lgDrO05mrWfD5OvMvWLDWmYdD4waKxmlH/mkNjdPDABrHAHVifx4m+EzPv+3LR1mw1peHQwMnEWVXtyO/mzKNbuzbw0D6LYMUPk9nXsuCz9eZC1iw1pmHwyOD4tHryO/VyNE7DKAEBqhP7cxDg0NhGqx16KHB+1mw1qmHQ+NlGmWBgp07PcDVzOzD6cVI5w5OoUzlS0f+lxqaXw6T0R0so6/O0+HnseDzdfhLWPBwI7aGpgHNaru+ceR/o6HxzTCAjnVTQNogPjR4Fws+X4f/MwvWOvxwaNzfjWh858j/TkNjuIG8kAHSBvKhwdey4PN1+LEsWOvww6HRiUdKXD848n/Q0BhuIP+oiwLSBvKhwa+z4PN1+MdYsNbhh0PjVxSNnxz5P2loDDeQz2eAtIF8aPAUFny+Dh/PgrUOPxwa3/yMaHQ58rtoj+5CBjAMpD0/I6TzdvhnWXAYO/0wwdUsuAc7/XnwWEHxOOPIP6ORY7iBfCYFFBnIz+F/LPh8Hf5M56AOPxwan0KUUtnVX+rI7+dqSmnfgjdgA+k/cTVW7N9qoiUA8yAwTRCpg2E6Vp1w5J+gRDwB8U8Mk/9vWP5fnocPLGPB5+MDs1iwxgeGw35cJ+LxtSP/a42Iw8kAp09TQJoMMDT4MAs+Hx/YxoI1PjAcGr87jWgEHflBDY3hZIDVDND5BPo8Fnw+PnAlC9b4wHBoJFI0vnfkf6+hMZwM8PVPFND5BPoGFnw+PvBXFqzxgeHQqMFLNFynHPmnaOM4hXxhGEglDNL5GMFsFnw+RjCZBWuMYDg8+vBWMNfPjvyfNXIMJwR8cooCOp9Av4MFawL90OAnWbA28A+HhkDR6HHk92hoDCcD3MIAnU+gz2DB5+MDI1mwxgeGQ+OHjmhewNUkn9O1aww4etcF78BOlWeWBQu3Xc9tH5NeR/PzY8x5o9DCr/cEnRuYA6Fu/TDBdSzYAMGGYYK3smAjt32REaWI3+tw9+CAFCHitMJgBLhBIIRVUZkPCVrAMl5kCL3w72GkMhiL9MGNikJPkuRBXEAsPvhLBTeO0WUqRbrEap17udWaPM1q7c+wWkfA93tTrNZHplqtG+D7oTSrdTp8x8J3x1VWq3Kx1fraZVZrZbrVWgbfG+H7UvgOX2G1nrjSaj11kdX6zKVW673wfSt8e+A7Bb6/gzwOQR6nL7Rafwt53AHfN8P34PXUfB9u9mma4O9uubhJ3nuJDmrV0bQ2QQ4UPy7rJFNa/TSdVafz6kJBj63sNtwfct83CrtvKM+68XogSXqeRcozK4W20Pf05u52uveCnv5pq56Ji418YqMTJ4d0svNYPdmwAV4ip8rJPQCuzopn6asQ+gQKvZ1e3NTAve606p1mLbfEy/GoOc2qo9HZjmuxGhQzzjCnMVD0VuyRg1aT8c67qA1NySR0PDIvvSlNXVkftHlp1fOjtAlo3MQlzsRZez5dtVNyqNSr8Mncjgz541LHR7xNrDNwOxLozi7cPwixhaPnGiqRW6J2VZZC8xCJwVHHx5RmmoVO+GE7wrTYW7rLtQ28+GWvS68rqS9yF9gVeV6aLdFfbpsvL0mzdrd2fya26iTwk+ATwiZqYSkDYRMhLCXRL6TIC+keeJv9YPcpesDWCs9DoTnwjiFL0mzodyB04MiB7w60Jh4VOiG8o3tV2kS5CUJSur8xHlg7wgHxNpjXxjkg7nr9IvtBueEWIa77s+5W8TPdshUrsUKtZc9ihd7Uzgwpt0nOPtY4HE5r+WgZDdlCTRoFiySYFWd76OtGZ9s5VZoPqetsUKVttEpT6Jk8WqW/Ohup0pNWPO5Mt3mTXdD1BLP9qOO0cCmJORap5T9cNMxG7+DDlDNYHB/wh3BdOtvqqBfm/U+NlZQ6DjE7Jcx+CtopSfco+R7FXaa34obnWa/T3WEA20rWHo3syvgVoCD6+xlWQ3Z+R0yt3KXZV8mMJCT7LtTsqyz7X9pXiZhWGUBZO4poJn9le5UiO9Vwh4yJtky8b8uMK0DJuJiO1lxLHQbBDAChA4S+AU/oBekB7QwN7Ws2UvlZBHPrhbgg1kx3EeIOQI78ggayrX+hSrqLsKDonJ5Irdy1eqznbC1cUN2ry9bpNqQ7Tm+4jF5x7jHhAbsiLSZhm/8SxfI+gxAjl5tDY8gPaP87sovwz0fUXYQrl2lHlZBz7xiJ+w64HbHpdUVCcvopJBluGoYApDXw/+9XrsDdPpR3VOCe7HNPHRS/q63sXUo2HomQIT51uMa4R4dnnukeh8vITQOxj04+/zogW9VzC7P+pzaD0OjP9dToT8jO7TCyRb7X62FM34Ep6LdYbyBP1dO1OGoZxx+xFPThf2opKNJ8f9MaKU/i5P9Xm+/Gwc1XRjtTVmpn6mCUnSng36OQee/jU6idqREa84bIaP3n2OB1W83YANuUd/qVlRAlmbz4aaRQ116gbsjDtc1vGp0nF4Av24FXjexs8J63a+meN3XnHuCt7nnTml+hGTtIZMN02fPfWIFzKLQmtHLl5w8yn37KfrQIeJ6NjPxU2xyzdRIwGbyUBFeoiWUHbh91OIFrs00y/8JtOzo52wZ86XK5oTTzAn4Ct8Ms9twO5O75DZA70Kbuh89MEb62+4NfQpEKCoCv7cHTF0UuMgIvXm0C1iblhR0fQC0//gkSBE9vEAleZR3dlZaZZ143kmZK1n2CG22CaMXS8UHFXE+b/eDS7lNi2LD2OhDVzFlo6nfDaPL+CAC811HPT2zU7d+v04VGushHB6EA4BXfqDt+HIjtB1kgjFdjCUlk4icaFwk9SIuVj2gWKWtsxOOkzBfNhhZQQsw4RNuH3BGykPZ/ATpX0H0/BWR98xk0SOe78yRum8L77Mii1xUlYq/eqnbqmh1UnkWjWrgx+tdQvdgNiouHs/xEm+S7tOoGzhYOX3NF/9JqLjghuuYWb/tPaw47Sg92lEDqeWtOT2tuybwhNffZ4UjNfXx4uJp7+/B/VHOJSefWnO3A+WvuF4fPW3NvzB1Sc/cfGKi5Kw5H1dx7jefU3OOvDVNz+7b9H9YcJC6wH3QXSYV9jn1cjRdZcLnFcUaIyyy0CveFYuDBr80stKFHilCGHin87ZmFE9EjVShCj1TelVmYJuRkFk4RcmDYkE+VZo7hzbnAhxx1G06XirOvF653nOEnwMhr5B64FI+VGPDAchE51kJ5gP0gxJVQggqNRyjvqLeSBc/AD6SMwSqLA95pV+xHATwImYWlYvgq3gq/y/kE+L1SiJM/Dxl9FQbK/mIhjnAMkk4D5PkL5cb0wIFwpjOFe/BFAOnKZ7tGyXItf6ncLH8csshOGwqwdqVUmun4jF/gOLLWCYXlU+V6BiB1vQcTpyrCRDK5hVKfpgcC8PPTTx/ozxSmrJ/vhvqdoghppO9jCj80FYFMSD+F4anrL3NrII6xcJA3nWk0Yzyao+4/QU8LeCZAHayPsXeV4pF3G/NIiXhMZB6pEY805jFF9XDsE0aTDw9oPXFlCm4wDP05s7BPIGTbAW2bYCAkq33ZHXVQGFqePz0m3DTWOiGpD37tXUZn2F1mvUynG/0RjK8X/IZeozR8yi67H2KP/mgrppdYev/AZR0Lo5gGcAy5RyrxSyXvOXqF8WTSgcg49Pex0Gn2odp9J25ymG/bAnJ7nZTXIgbelZyHxRbFTe8+hcC1luoeM+5xeehyGhWE300xYjixImeLx1Lc3SPv26J3tki3WEcWHnZ8UA7Cj0V0tijgIRYehppskQFe4F0AiRC/1kdD/BR3FGywyqZtfOFYawGatju8RRFaJOdeqbCJvBjQ6RLr3kVDK8Joj86zSr2G0Uf9hYmyswUvmtDFrI4DxiUe0AHx7mVhSWK/vsIsOvfqxcImUBMRC7kQ4haLP+gnBCS8WLUlPwbvDCoYfWCxSxLeIjgHBQrOfItUuH8Ly26nsVV27h9d55ac+8lffqIGGgDJnenoPYF5P0q9y35FGfFhmgCQHF2HYXOBM6ggjCV7PbrRzqYV7urQF3dAZ02Z0OAqIBei7NckzzfLn21xGwOeWaMPLXaRRNXXBL7GgHv0Ic8s8P35HeobRz1HH8IrMwoPZwpm/h5ydA/en+R3kcqd7DzfYp/zPZBa1a95svM9rCa82RfqCa+bIrjdm50UkeenOhoq48odmUK44lrZ6R8a9TZkvGPd+EcuTMacWuiVVeSVbSoMK9YF0De+2Ce0nn4xZCWvfwSdcJ/a4OS6FeyajWXkwpciLBe6uUdPbsTzORERyqbe8SKVh+kNLn2Obuhqv/hI62qdNtrVlhR40uiRCDf5mErPFtxn+4UwklwXidoMUUNT5LkmOdHRWBm7abTj47WcGI7bNKHSXN1DD+KPJGYtutywDC+9Ib/djeULu4h5B6Ud5/1Cjz6dLnKx5vMh9elzkdmaz7vYkm82yQ5v8yYPgFeqOo269bfJzr4t6fROoAn73HgvDQwvG95SafZopjPM1Tj0WAjPbgaohl4P5+zccjnein7SNa6ww02cagrOWwwDTWNOKuXiBmy7bjIlEogWowAkP9VNJjBwwKKdfUZnp5oEO3msVGjeIoflz9J7JpSYQ5wci1/OPmhT6eEJn0H7nlVQRNJ3o+FT0FsSRf8ssXGvFCseUtSwZ34EeofxnurPoJcYw9BkPwPv8C5qAwTSWNQ0OaaBRB41kVlLlEIT1dNEZpYoRWwk8MESpUDoDEzU5D24Kb3SRC2U56RAD4nbsrJb0S+ySO4U/aKJILbMgwHae7Dy500Qad2PEMk3Tx+3xRPHosk5GNPrrzxYHcA+CmlE/2RlkU3KsTTmWPFii9A7RfhHckbpmFHCqp7sdclVPanrYrkX6w611cstdn/VicmHvqy3++0HIxoDqAtospKPySy3bEghuz7AplQsn5LMJG8UNtPgN9j286z2ox7DCsfHPCgm8aXwTJE/zxQsHL1FCIYmz/XGhmJ4GhvkPBsEO0ozM/lr5zpACxEljCKPLJWsxo+MIMRlCt+mfwRgxJ6r+NFiz3J+BMZbd6dnuQYhBSCMDVmp9yI1aYPxI0wakvMmQug1aODU8Sl/hXjmSj6VRrzEc+WtNKKaMHlIQvRcb4MOizKDnhzcR8U83Jo5MLhGFPo7+3Ru7B6qdPTYe0CEDtz22iWkZDr7+NHkd/voFbYJRNqHo30fjJUNK1TjCPv/j+wjNL/3v7ePIOAJcWYf4YHyofYRppVr9hFcg20jHOn/0xdtf/7NpIiNguUQ8x1Q9HS+pI6bxlqDxfB9dNp3GLX5yM80cvj4kSP9oQ/Jnk0Dhg9+YoYPQoOMI0SAxg0GSnQVA4YP8iwFaLZv/QRV3EarXRy5sjlqzmQOmuPCm40yS8w8WhwithAeWm2l9ydch7UQBi6i8DbH5+us6afd0Em/KCDrtjNZujFay10y6DY1j2kpORZUFOnOTs9EHBgUoVNJPkYnVLiaZ7EDOA9Lzg6f81UQY9pQjCl/oyytdRTIPewUpqOBv7QsY+AUJnyPwZtB8U6pFuRiZhiX1htlIeybr/iWz1a6Wy5u5Q3GL3ymG6jB7FbfBsVY3tH9ycVCZ/ppR/faaR5TGU5IF7iV5HY2tTMeuWmZSc88U9jBXHpblgGU9TufjagE1c/h+DR4/vs/PE8E6vp/d6SoHc8/Qw7BP4OMOmh+3ZzeJJ7gjIEJzYmB4uBmoigR3zjNlycsUaR/yO/+j/oH57313cH2YG4znMcezGOGIfZghIXMYItqD8Y0vD0Y3O58Pnswf7+Hbg4/jz0YPTM3cyEzNUPtwbgMaA9mebQ9mCM/UFswVRCiL+Xc9AVtwqwxDLIJg2dy35yAbMfbhVa7TXjILw7aVzZOE5KlaIMYT7V20CO9ljI/zkE3fKgopBNS0ZWENUsV15Ji8g+6SkPN3Up57a584rDjeIsWbxWhnUzbpx3IJMo4YBmd43Aq9/A4emgcN/2TL6nPmPHUZ4o6nchyxpWi/CWSa4mcv1RyLZXzTfmSy0RkQIHgYhADXIDWvexH6ZmmW9+PiPChRDqVFKpwE++4AYPGs3FOpAO6chd/E7lsApq/WO0mp8ZhN7QWF7s9JnfZFzdbcTpJqljigdF3qZJ8kk6UShUmYACWIiVZ98IoKxoKnKze7NTqJvFvA7vwHuXjCkjvXnjFrA3UoGNJvdYe+V//D9qiMCe46+0oXj3rf5KWC94Fad/ZDGwyePlu7a3gPXX8/j8YP+7a/b8fP5LxYD8bP27cMHT8+H79+cYPZcj4MRHSvjOKsnrdzTB+jNsw7PihwPhRuf4/HT8a1w8CSvwbcPzQxluGtG/9UKRnakijSSA+X0U8hnQImomfyUfORPK4A/OIoXlYEfHb1tNYHZXCVIbiJQzFC0L7yfsCWv4ZjDmzDvTG8AWIHQycKOsjA+Bgw7ZoUjdi2LZ/q0IN2+agYdt61bDtM5phW0IN2+a/
*/