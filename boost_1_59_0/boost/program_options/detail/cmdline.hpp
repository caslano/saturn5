// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_CMDLINE_VP_2003_05_19
#define BOOST_CMDLINE_VP_2003_05_19

#include <boost/program_options/config.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>


#include <boost/detail/workaround.hpp>

#include <boost/function.hpp>

#include <string>
#include <vector>

#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4251) // class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class 'boost::program_options::positional_options_description'
#endif

namespace boost { namespace program_options { namespace detail {

    /** Command line parser class. Main requirements were:
        - Powerful enough to support all common uses.
        - Simple and easy to learn/use.
        - Minimal code size and external dependencies.
        - Extensible for custom syntaxes.

        First all options are registered. After that, elements of command line
        are extracted using operator++. 

        For each element, user can find
        - if it's an option or an argument
        - name of the option
        - index of the option
        - option value(s), if any
        
        Sometimes the registered option name is not equal to the encountered
        one, for example, because name abbreviation is supported.  Therefore
        two option names can be obtained: 
        - the registered one 
        - the one found at the command line

        There are lot of style options, which can be used to tune the command
        line parsing. In addition, it's possible to install additional parser
        which will process custom option styles.

        @todo mininal match length for guessing?
    */
    class BOOST_PROGRAM_OPTIONS_DECL cmdline {
    public:

        typedef ::boost::program_options::command_line_style::style_t style_t;

        typedef function1<std::pair<std::string, std::string>, 
                          const std::string&> 
            additional_parser;

        typedef function1<std::vector<option>, std::vector<std::string>&>
            style_parser;
        
        /** Constructs a command line parser for (argc, argv) pair. Uses
            style options passed in 'style', which should be binary or'ed values
            of style_t enum. It can also be zero, in which case a "default"
            style will be used. If 'allow_unregistered' is true, then allows 
            unregistered options. They will be assigned index 1 and are
            assumed to have optional parameter.
        */
        cmdline(const std::vector<std::string>& args);

        /** @overload */
        cmdline(int argc, const char*const * argv);

        void style(int style);

        /** returns the canonical option prefix associated with the command_line_style
         *  In order of precedence:
         *      allow_long           : allow_long
         *      allow_long_disguise  : allow_long_disguise
         *      allow_dash_for_short : allow_short | allow_dash_for_short
         *      allow_slash_for_short: allow_short | allow_slash_for_short
         *  
         *      This is mainly used for the diagnostic messages in exceptions
        */ 
        int         get_canonical_option_prefix();

        void allow_unregistered();

        void set_options_description(const options_description& desc);
        void set_positional_options(
            const positional_options_description& m_positional);

        std::vector<option> run();

        std::vector<option> parse_long_option(std::vector<std::string>& args);
        std::vector<option> parse_short_option(std::vector<std::string>& args);
        std::vector<option> parse_dos_option(std::vector<std::string>& args);
        std::vector<option> parse_disguised_long_option(
            std::vector<std::string>& args);
        std::vector<option> parse_terminator(
            std::vector<std::string>& args);
        std::vector<option> handle_additional_parser(
            std::vector<std::string>& args);


        /** Set additional parser. This will be called for each token
            of command line. If first string in pair is not empty,
            then the token is considered matched by this parser,
            and the first string will be considered an option name
            (which can be long or short), while the second will be
            option's parameter (if not empty). 
            Note that additional parser can match only one token.
        */
        void set_additional_parser(additional_parser p);

        void extra_style_parser(style_parser s);

        void check_style(int style) const;
        
        bool is_style_active(style_t style) const;

        void init(const std::vector<std::string>& args);

        void
        finish_option(option& opt,
                      std::vector<std::string>& other_tokens,
                      const std::vector<style_parser>& style_parsers);

        // Copies of input.
        std::vector<std::string> m_args;
        style_t m_style;
        bool m_allow_unregistered;

        const options_description* m_desc;
        const positional_options_description* m_positional;

        additional_parser m_additional_parser;
        style_parser m_style_parser;
    };
    
    void test_cmdline_detail();
    
}}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#endif


/* cmdline.hpp
SxxvL4wEPf4i+Qs3Up5N+8OmTV2Gc4A+8LDIhUOyr1AWFhf7RpMYdi9WGx2vNoTaPG+/GAhD6Qx6bj4ZVADgBNjzwta1QVJCyB410Ig7/I3OVx6DDlfUq23IJ4otMCbFJui340TYDSURSvf3XxQvv1Vg24Eh4RxhKMaEoi87u+f7q5uBoVdbPRQ7uLvx8cQHe3+om0AgkdJLA7zE4Owcw72kTjlPCRCKyPDWbUVf934S8rrMA7xR8Y/W35tfNfCTgi+qv3j1xjVdbLQ3mv9SlDieSk3wvYlpqWtpoUw9s7C3t8dVmf+ZI8xQ1rOFGqzriiD9j3i9NNr1RD7YCUMlKzzMnb+kLyQ3LvqW+8g6qF4gl5KCfKDf8Q2XPAYzOjZ6CPhGVN2tbbEzZQMi47S9smrPfMdJ4u/cgAvd6vNsltpods9XYyT8liv6Svgme/elwLu9vT2q2fIhg8t86OHuzrnB5fibuqEh+GuB94lLpAE7R5llckrKpqyx4kwr3kM3gp+w5PbW33wHhpPw0RrDTpQ3x7OPLkJWHYmn623VmecklsdhlDflIEh6fu1yUtGiBsqbRZB47mkRtCxpAd0PIAlSxrFCMUNo14Nitvvci6ZyhVP95ix4PQGN5pwDcP4RlqquK19qV+lIzpTh/2MNEpTG8fgP425nqhbBKYAKCffh3PqdRtLOxFsTuNpgOeE/mcmHcPufAu8fH73P8hHeP4y7myvLIEGJq602CRzjFaG/co+4RengoRjS0dv9YdQ9RskuO4J/Us7QJQ4ErmAqWb4jDbG/INMBpJ9xnrI44ShmXJIX/92PAnvGboD8UNd52rny0BaL3iKiJnJjNz22/eRwllH3BCSrhlogIW4gRZws3dwaNbG/qsPxa/P1L5D3a1RnBFYA5vobj6QBTcQ9gpAkeoG3Jqi0NGyVUtQznsof7wAf4TaVasuMvAHFOYYwiCyE6tnkzRWjArw7EO4wz2smKlnzNb6xielB9D9cz019VwilmLer8CV2Zjgx5D/HMHzLpsoScDCaqYPEo0d8jy2KT4unYdz/TOjPdLJh0cSjBl2gED/e20PzFwcHTBP19gb25Cufo1bMTsVnnSFoNGxb+DqYxWKHhMtJGBiQoYSOxmcK483NzZkkCpP828MYmUrtPzBDZUxB8+wsRlFUVDRJ/ZiUzV3pxWUCZGsT9AuavTbRlns6pFOoGvAxlCBqZ/NIIfEoMvRu6DJ7Ao+Stdr3a1TvTbRLyISKk51GqisXpg8TOvm7BtosbEWdjyYyvEWdVxNDYwycl9/UhxhsW7qw31tTJA/HXuucJj+I7sYv11th3+SHOJzsOX8reFnaZqunqe5lhmmUfTu9HdVqP8Aco+P43FZM/cEjnoYX29dDA8ZQRSLGF/J+SJ81F16bZeRG/CIXR3Yk4mhChK+/3bswm4AjRK9WI49NbmdJizMcIymesgosN8gQX6CZUidJJ0HlygDDB1nK7PsmGSCAecyphDpbW1s9ZBO+MPd1abtzF1s8O3t4YDOqD9G3p1uW9Z5kCxgYvuL/CWt7UjlJlZ8Xy9lMGfSfmupOMlCWk/r57VlgcdCXAcMPT7gLKaM91qz+/Zz34eLXQODFBu4mG2+BD8gRPyso20CFcWRysh5drjQlKUkF2uDi7Dy0AvqcZ+uJ1ft67FvjsO2PZ25uDtI+dHEAgfkl8z7iXsjeXIIg7ymvZG9+/fu3qGZ9LLdCD4MI9aH/48Zu7b9jHMr/UU7wUdEX6zYon5IhAoBQf5DyQraHULEJgZWcoD2cD2vOmqZuiY9JyRSmeurBy5OKtnCTuKCLULk8cokYjnGToJBwv1jZ+i0e7qnyZM9GM0KN4hzofi90gIzghSDpLxmfhaOkVFn+dCd0gIpwLCopLmUE7JZz83ndyOCxQrn7HCQa9nA22A1h9sU6vuovLy//hR3XYwONmG6+fxfqov83PCxlp072r/jfV2lvAumyISlFRbS7Fs2IiT/BOLqs0aQCWLR4qPIl6vGjFmo6OihJ9Cpwy3yQGZ9Gyi53a5h040eEKFu4urZTeEIPuPz9aiocX2IkCM8e9UuRtGPlH3goM3XIRDT88PztzOOxvKNoEgp4OjawxiNM4tj2u8krFQIrEBs5i4HL5FEOw9U3FcZ9OrHvvtV0x5cH9wUUA1sGGA7aWfO86UhAvZrmDnhmDXeqP50vG/C57h5uI66x1GmwQN3RC0th0e7vcDs3Ab89RtvOXl/PbMO8sT+ByWMF3tmvHk7nA+5znRjGomoM2uGWawyDRTyuesHvz7vP28DwMtW8zyMB1B/bBy4Pq6EVtb/nhmui2CVvL39vNzcm6MrZ2tpSZra4Ota1AgeEaXlFfXHW3HY62ldFnptRImNjsSRDl8lzNjfeHi9wCchJleZN5jvjSKd91ezsNNaSrAgDR09MVNakenniqOoPqiX5WSeHH/TraYVH4nI88FA8yc1RUbFuzR+b+Lm5sftbMNCsHgPz49VIKTH4xTN/IoQihSMgIiIjYs+1UMmTSryDN/ySjdWwiG0F9Sq0sJq+PA7pccG3Wc3/Fl8mjl9Yu331paBwt92x5SA1MzNDKsijPymLrK29trs8VDGe20C5XC4C0Z/Uor757p2clA/5AtmWXef/sChir4EyGXQ+L0isOz8c//voCMivZTh5V9DRWUmKiIg4HwjHBv0h/iAds0xWEoRfejyZDXb+8ZSIeveNbw9FUpmK0OMD1QyhvoueKgIxWYCbQgGEX9AVvMf0ZpuYnPyAWg2/l4RphifZRZUa1x9xGEz9b++KKihdEocIxYygorqa7qRytNvneWSz02P0arNzNAKXpmVeIfhJIUIS4Tacaginchj3392uWpDnV5w4FDN8STuqVodt+pNjXZKOpyZIE0ZyLU4ryh6epO+XCBkErkSqnvhwbMpEZGwKzgJLNawS21q2fZZ/IkHpsjgDKGbEjWWi+7NFclUYzBECIc6CBWpt+JPCAq1yorQRXgi3cat5AGAuFT9XwSHV74QflVq4BloPP0rYJy9xefieBBpHyr8XoZiRe328cOGvhScj+3/cDiM8evw6ligSM+NrtK+TM+pdez8Yxadv2j55do7opqWhMW+8IhWwBqAdD2FG26xaHIwkRDdCbocpEZxSFGRkEIXczggy+O0/k4i4V3ncoyoPRz6xmfEzMTJSRbx6c7udaarr6Sle22LxmYvFPCWzaP/4kcDR8xL06OJSIPxfL/dsbw+7q4NdcpzHUM7zdfmI4i3tjSnToy/TpVP9UsTMu990+pTUDxM5M/sR9t6hKe7fc7+afW7Y7mBgfPczE5xQ+UoCQjJVqHL3m0sv4yxBuAV6W6+kyBl8Gb8tNQMXxlswTPhmxOuIOoql5Z/6LlExFdvNVuVbwSybA0lBAvMOliXVkPr07rjPaGgLbBZu6ubCaBYT6kFul0io8XFyzhMcvy4xtZRDpZBE1PP9yo6TlySnp2DD6j3M0dVUQ4UWgtBNPYstXjPvFFcW/1WlMMXIOS8kmgsZNCXXVeP8s+MJwZgYtdYKSm4OjvJT0eBN5Ub/1Mjeu3TYyIP5tL/Kt1g13Gb/hF9dH/Q4hiLqTdqcbE0ecNkqjVwdlLuCh5jL1jcNF20TI22HoKijOqdVvupWnqpjRRD8aIWwsvbriuBEH4nM/s/4Fhdn0L/4VOEhb2H66rP0s1NXCXIi/I7scHPssn0rwdgYHDl22D2uGA9qnMBh3gue9neBZl5YFscdYoGhPuFrbWK+rGaNmIpQnPW/C7H6Ie4YhZwyw4gmrPO7gQJ/AFF0ErYE6E/pqj5GYfvSPhUItjT9ySEpm2vviwV2onxFinKqPOoBTNqslbtrpnZYEbo5d25N+asXv/VEDC7PEup+bHBCBnSE0PjjBte8PoU9xlpaYv6D2HQcOXa3D1B07uUxtCzgd6kh7MgZd9nZeRBk0S3ITv1U1RjPa+3g47v795o+3NWPRxxiOWj2m5Al9ElV/InG3otw7e+qLcPkfVsdrEzA465p9VsjjfhS4vuG+PO/AAQs+9N9HHsHvpSSuRqYT7ZK1Po2uVU5tk5HJ0tsGTG6SKWWdiqHhSrjXE7DPH6cqQ2JMmtzjTp688aZzVW/v38mOs94DeI/mSZVvRQt2k/It0/SFKHA3GcGljjdIvCw8uCOa5oYwd7rdLjot7J+hlsxmFt2EC9ay1Q1ncjCsOqecX6E/RKLaluiHvXdy5sFObJu1DJJIkGRLiFmmmWXcPzu4C9VGVyJqATdVOqI9F9IQ5gx3jMRiwXsl5SJxvjrfymRB3PKkYpiBoWaCp/uqBh6GKZtHPMzIfK0irkVnqOJXTOydLhEM9s3mFiaivQEM5jW3Hgpc19tcmmVCudGMThkZd68gVXFaonDk0V5kt++/EjuUktg+S7shF5MbVYvHao9SXBYQavzEMAf7TZ9YmQroWGIxMtv6ZjPCADU7jKEc2zXfKkQlfpejKe48KtCFF0prWIu6xDR4kBJaiWuUbcelo0vKLsJ9GXWaKLx1uxCgK+/rRwWjmLaqhfFj6cszLsn89HErovWsdeFOZp8odAP3vUtsrQp6ZejmZm8jo7mh35FxVpwmgJU7qK1qXXPNR98hBweWlqxB0b9xiNyyNTDf9FqseIwWredaAqiG/BXCgOnYryzkTzpc//fKji2HE5fYmo7Ou3SW7t+v9azMGh5EZcgi/59bf0PU3NLwfFGRX/f06y6zdlsE8FndNZseh6iGI7eruGp/7cqNuR9kvkDXdBw6eN5P915MKCxM46yhi2HxeBlXRcUb/WcF9mJlTxtVAda/1PRJb31r8yHeRn3lYjlxxH9z4b7oSK/ohbB5dDc68Pvz0sZqixdU8YtQgKCpkrhlOK3XMKiUGdXaOh+R4e+lwFj7lOtew1ix5+3CeBC89eSx2yt71yMcn/lnu18nlbEBpttC5MVMU8/MbGw4dhyHiYcpNbkq8XLuSWES0TH48jLc11nSf+jjSeaNsBzTvJxQJIn7tWHzmcoK9+4WrBXtOPjeYCuoXmkQYhrjZObYlZZDlddDj+PnsX8t5/BPAqhj6dHJrKPbXk1nu93iZlzUj4QurK7yGN2MXLAT7dZPxvzVCVj446jZh65LFWxWT4b16UXOYgf9Kqm1tUXqj5u9dzuD50JpgT83tJI4GK/njijgR75zP4Qer26Ju8Cm3rWrAPfyzzYNriWStinAYkpmtw3N9Xf5JY2t8leIKrHHxcPGl5xgHfoLZTNFPbOCutJDxryV8ml4yo3mb/HG7LFIta6/fias+wU3taObfC63DnucGrgMjxgaYueB3WSTFjDeam989Ef/lDbzLqZ/A4yguY8gJGNKQXFzwJpXMr8n3O38pbZznI/hq/YttufGQIdNttrr0lVF3xt987cjH3s1nOer7oe+xiwj56vOuz3F5yXs/CNwLPtlLQtvrjrnO17iyFXsWO0z5msm1xPlAy+EAPZWjxriMxopn7ulb8Jn+ujb63nIuW7+2G7UYbI6zkfC4Ob9GSMAqriNfmi7LRPA9hWaVs5Q+yKB1r4QC7nkOP60Ej50ECDr13Lmu3MDJHLCTy47rnVmX0Idfid9xi1taZPYdvFQ3wXCzy4C44bJtP33C44Vs0DECbdlHXqlWmrpCcD6LetdddyUvVfe7e6st+XBdjqthXaBoziwuR6xNDEywQsl1bfnWCeAbxoRt4KF0RQ/F4eKBdarveYOACrdyU4A5p3eb8NQ6wthEb/relZDp6sgtJtshMNXU929TkLJU75A/lGqejifRdi3QUt0b98VwnZI/cEnlc+gW8+CAKGqltXnwfusXfB+g6N1+HvnnnRgE2k5w2aJ4FY2AjI2YntVqx1lzkvMCseVPuQQu1gj+0XaDOiv24+HBvqtD/UVxQnjpbEoBrGpFHae7HaaNqn0bgbmscReDqfFrRvNb4T6jXeK+QDO+Hv9YlVpw4mFcqNSsjAEfwD5I2Y+uFNUqVTD8dPVx243dOAwf7xk866Umug812dqvFNO/57B1wDFnvwhzPDQTcIz7lSq7fMQXB37+hwBjylJ/j9RdjO/gPzgNyHfM/Yn6g2Cw3kehWQ/Om07uIxp+6XJTqrXzM8f1lVsP34dpDHkl0YjVKrhIoiP5kvG3JsVyb6pO122NXi+c7L2RedzilkW2DlHXSizu/+960xCbf7V29vegtLS8nVpxi1dhf0i/VUpHeN+XxGW4ar65CJRGiIWIpgWjf6K2UXLF8oaX6+N34y5Rpa+7u75KKPrppaI/zYuXt/jYpXnXgjMbc7Ud+6flxv6oOw/LoTwh3PeD6/CBFaKznMcuyv8pGa0M32wTqmVqQnAj8ULy8vNQNNhNdXdkZm9sCGBm7BZGMYyx/tjnU1MAY1aIzTYgih77YFhYVwf7HTpAYDP5dXCCMg/8KSNDQkb6o1xr7yaJGEn2J9JLdezUWympuX9LGlcf1pHxo7gWE9so2Ri93aq6AtbMA4ElT6R/mEdQPxqnUs3+Y8fGe0Kmxq+xIxjoXyoPDrjRaRxHqguvVYbbDG4HtB/V+0KXLRgBhjatcdp+5SPHc+ECLdlYpgmdRhJCujWDfy2eeogq5qHCyfsd2bVzTBU3bE05d3xw9NEl5e8pB5zB8zK0boOY9udTbjCp4im+gi7l47k49Wpi5apBcTibvBF+ZquS4YLam8vVeiHHabLANT/e4j5cLIoeyUmkQdBRcSPAsUdiEfeCSKzNNSlo9CK226weSnn+1GNEy0C5BIkIWpQGrI2ouUatrCL0pnkt5QhOyqRwn9FGTRcLryyuevze+iF79eEJxpyZ27ydWWNlCv+dylJDUEknk9JEvK4P9M+8I1X+bsuHcWDBpiM4CH81f1sRk+i+7YW4fJxlHq6XU5tlSgdlmR5ndvoj9eacz47hGQOQij+0OZHPPaYBhEYa1/t8MQZa4X/BBGZJj2jc52pFhbW9/9uk4i6LOLYSC4Hft+vFPUcu/4tOEF0YYnz5V9OUjGdoXazFiS6KXQW2vr79I8klmfDe/YvCKIHgtT3bwDJOQkEEFziJQszNZ6yK4erhJWaVibhjkzq6uIm4Ie7m59g1FEBWVlyD0ve1GkPc1iX2i4/38HuDwHuDBLCAmDdpiS/PxYcowyJRkyhhr69DB3iJFk9vXjmwenYegORAEFTaNOP6MWSeL8ZacnTJWQ+LKrZKwj+o1LSIxpVMHsi8JTfR1SGClgGXgN9eRn/SHD+lJfIK+cqm8v/W16hyD1oFjGVIGCACsdiPRpF/2cnorpL7NXtrLgOCfUOBDHaBEFjNnY5wuXGPPvlODpoNyvbddehrUngGDnC6LmJ7/Af0YVJwTMbyhXPE7K2qOGN0UzujIl9vSvxFucvBsv0KUXAbhvtWOGhs1EHdQ/ffCJfgkW3+KQ4i0iqB97uuWQfJaNDBvmvMr4VuaG5osJL7uYbsapsPdE+RuCDrbEFjjBxR19/CrzXHEUL7jshhmpJMDrMzdIXwYz1IqbVWrLKIzM1GaqRu2pTo2Ic+j08ME4fzuMEWngtvIKMqZqr48iDcMuWjq1S5kBLNYR9h/Tye7w3f9FchwmW+jN/9LUF/o13M0goSakgm/osYCn
*/