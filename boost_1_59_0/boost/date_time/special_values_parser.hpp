
#ifndef DATE_TIME_SPECIAL_VALUES_PARSER_HPP__
#define DATE_TIME_SPECIAL_VALUES_PARSER_HPP__

/* Copyright (c) 2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date: 
 */


#include "boost/date_time/string_parse_tree.hpp"
#include "boost/date_time/special_defs.hpp"
#include <string>
#include <vector>

namespace boost { namespace date_time {

  //! Class for special_value parsing 
  /*! 
   * TODO: add doc-comments for which elements can be changed
   * Parses input stream for strings representing special_values. 
   * Special values parsed are:
   *  - not_a_date_time
   *  - neg_infin
   *  - pod_infin
   *  - min_date_time
   *  - max_date_time
   */
  template<class date_type, typename charT>
  class special_values_parser
  {
   public:
    typedef std::basic_string<charT>        string_type;
    typedef std::basic_stringstream<charT>  stringstream_type;
    typedef std::istreambuf_iterator<charT> stream_itr_type;
    typedef typename date_type::duration_type duration_type;
    typedef string_parse_tree<charT> parse_tree_type;
    typedef typename parse_tree_type::parse_match_result_type match_results;
    typedef std::vector<std::basic_string<charT> > collection_type;

    typedef charT char_type;
    static const char_type nadt_string[16];
    static const char_type neg_inf_string[10];
    static const char_type pos_inf_string[10];
    static const char_type min_date_time_string[18];
    static const char_type max_date_time_string[18];
   
    //! Creates a special_values_parser with the default set of "sv_strings"
    special_values_parser()
    {
      sv_strings(string_type(nadt_string),
                 string_type(neg_inf_string),
                 string_type(pos_inf_string),
                 string_type(min_date_time_string),
                 string_type(max_date_time_string));
    }

    //! Creates a special_values_parser using a user defined set of element strings
    special_values_parser(const string_type& nadt_str,
                          const string_type& neg_inf_str,
                          const string_type& pos_inf_str,
                          const string_type& min_dt_str,
                          const string_type& max_dt_str)
    {
      sv_strings(nadt_str, neg_inf_str, pos_inf_str, min_dt_str, max_dt_str);
    }

    special_values_parser(typename collection_type::iterator beg, typename collection_type::iterator end)
    {
      collection_type phrases;
      std::copy(beg, end, std::back_inserter(phrases));
      m_sv_strings = parse_tree_type(phrases, static_cast<int>(not_a_date_time));
    }

    //! Replace special value strings
    void sv_strings(const string_type& nadt_str,
                    const string_type& neg_inf_str,
                    const string_type& pos_inf_str,
                    const string_type& min_dt_str,
                    const string_type& max_dt_str)
    {
      collection_type phrases;
      phrases.push_back(nadt_str);
      phrases.push_back(neg_inf_str);
      phrases.push_back(pos_inf_str);
      phrases.push_back(min_dt_str);
      phrases.push_back(max_dt_str);
      m_sv_strings = parse_tree_type(phrases, static_cast<int>(not_a_date_time));
    }

    //! The parser is expensive to create, and not thread-safe so it cannot be static
    //! therefore given a string, determine if it is likely to be a special value.
    //! A negative response is a definite no, whereas a positive is only likely and
    //! match() should be called and return value checked.
    //! \param[in]  str  the string to check
    //! \returns  false if it is definitely not a special value
    static bool likely(const string_type& str)
    {
        if (!str.empty()) {
            switch (str[0]) {
                // See string definitions at the end of this class..
                case '+':
                case '-':
                case 'n':
                case 'm':
                    return true;

                default:
                    break;
            }
        }

        return false;
    }

    //! Given an input iterator, attempt to match it to a known special value
    //! \param[in]  sitr  the start iterator
    //! \param[in]  str_end  the end iterator
    //! \param[out]  mr  the match result:
    //!                  mr.current_match is set to the corresponding special_value or -1
    //! \returns  whether something matched
    bool match(stream_itr_type& sitr, 
                        stream_itr_type& str_end,
                        match_results& mr) const
    {
      unsigned int level = 0;
      m_sv_strings.match(sitr, str_end, mr, level);
      return (mr.current_match != match_results::PARSE_ERROR);
    }

   private:
    parse_tree_type m_sv_strings;
    
  };

  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::nadt_string[16] =
  {'n','o','t','-','a','-','d','a','t','e','-','t','i','m','e'};
  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::neg_inf_string[10] =
  {'-','i','n','f','i','n','i','t','y'};
  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::pos_inf_string[10] =
  {'+','i','n','f','i','n','i','t','y'};
  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::min_date_time_string[18] =
  {'m','i','n','i','m','u','m','-','d','a','t','e','-','t','i','m','e'};
  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::max_date_time_string[18] =
  {'m','a','x','i','m','u','m','-','d','a','t','e','-','t','i','m','e'};

} } //namespace

#endif // DATE_TIME_SPECIAL_VALUES_PARSER_HPP__


/* special_values_parser.hpp
Yxfs+VYGHi6EvKEVDooUY/WBukmPk2GLq+k3P5L/541O7xCjzwv8NIGAh7yktcSa+K82ulxxEhIiXLJPXQ4xKT1v8VjKZSo+UyPqROoldqpaeUutI5mI4/EqpKstHvJkkEuu1z8A0lBL15uYMz/uQT3val/Ffz2kX5VuZIxxJ4FlZZOHMqr5vO/ZeGlFaN9AWRl+LJXx0zsf8Tr2GU879yedtkIta5Nfq40ac9YnYac3NGoaDBYf9LsmQI34/ilFGwfg0EqH9mfs3Hr/SFU6o92IAEBBtfJ7FsIWQWyLyHvnOtbnr1Vru+VBrWhD9wx5W8H5jdL4Uv0v4J/yjpltz5Ifcod44CxdMWs9s0vA4YxHhwmD6dEhaB0va+eMYYcN78fB1Ansyb2xt7cqoLm6mjpFsEU+pQDHIqZoLX4y0xnSt9RLnHt8nQ9r6m/X4O86Od+WTF9pA9dCqKk2gJ48GAFVgzNNZZ3s1G+9WywT+8pN3O7RzpI7SUUy6W4Q9FZeBnL18bqKUW0VTF0cPv4o9FAR10jcXBx5c/rHwvnQfUoZwGF3PsJHSZ3GMoe5NJgTmdHw+CdifnQVINkAM5cYuzeeDSXPK+ki5IGkdhN2r6FWAYFWNuDsNzFuOXrP5mUt7gfddUAU1RXzQWe1YIMmo8rFJoLTNP4LM7HxgSGIMrspOi2T/IaGcD5LiFfUI2dJIezwJPfbvz/TW/mnYq67CyiPl0jr6L0EawdPYZ7aDOpzv6RgesX+/HBfa0kXiOmQQF7N9hkVBneUqN9lRnL5qkaL9W2Xl06y7B1af1udKYv1Pdpq1X4pJL0KUz1mM6yuuwTaro40TxNnyMQshl4ZHFAfkp+1dQATLCWZwus6/icqSgeaVPEL8UHM0aLrUxYAN9w/M1uBt1//847nR7HSBqlYZNhHw7pjrnRCsDjr7kKJEUQCFxvDjCkiKKmA4/J9az6plARSmGqAWCMNcE6y9ZlasDKSDjlDOdOZH40SqTN/XdPi9HED+uF6KsuQ464nvzPJJWRchEAhFDrA9cavY2ZogdM0sfHdCUH4eJ0MCyqUvQCfMd+pREwKkuc5X8ArwrkICJuVTHh/wH0fyUEw6ob5e8AN6dDPMJ53bhYPCULLjTR+W2TTu0UXrVgaXiUD/aNKeN4DiTn8b2XavKqGJVTJYJ9H0T1zlERJ/T+5fKPbPv3V/SU2ryQY40EAxIR5sfLQHOi+R9N/Ejxpe2unXJveddG9WVNPBaJmwa9qj+vc2kaHfLTiWEQ1g6d/KIn9tRz+8TdMj41aE6XE7qQXrPyjp7+wB5KuigJZwRddooyoXbISGTVKsT58EOZ/xS7Kr8VMvV4NDMyePWPtC5re4MeRm0qOVoY4GDKgH57UtJvUKrYd8AllUM8HT/4ZIU0GBHkbQRx8APPTihnz3VZYfLQE6HgRrlg0rRgrY1xzFs1BLYxYPnPS2n2SddQSHn5Bw/alAF+3P7WjSxkrzIWSnR4LZW5xs99aOPfco1X21HFPKXqTLQD2qa3jYHHdVDGw0d4jIOKYgXDTPuZrl0LEWPC40duP1crBsoId6RSu8DqTmOo718SQfwy0wHpR/7v1beSkj4EGCXjr9QUftWpXlAUl59kyQTRsa3y01XUBibWHjgQMWBYQgoKbN6gKsZmR3B/YnvEioac/F6GPyZnqx8LUR5XocAZ38zp2zZSbf8zmq4M7wguzM1ntYRfdD6xZk1cHzR0A30cGb0VKjMz9DU8YqSLHIezCr70fEUFmB5YAju0QmD1jHyf2NCRF++B2SsaySqCNcx8My4qWitHRqSixKSyljLzm2OdZEyHS8oaMHBIoizZ15SNBRDVHH29P/OyTfkuLe6PPEM/OexqCFmboYt8H8+hNlmG6tFjLxk/tCoRNM9sDmC3z14vHV1p6vDdjZScIdc/qIcsurWHexeaxCrx62vwmb8IPli7eKfJ9ZTsbLZAY222HBk9BHg+XZa8l3d+1QI9VLuoliqjgplPK+MUnAo5+GMlcexftDy8yosMUUCvhxbGaS0SmEeD0n/LPiVBQiGgYkrBueYDOF5akbQoyJ6rDJkLsZNLuf2q6Q9nIs5aFHWGo/gtDoiTBsBDvdPeAXwtSgt2MIrXJuZN+zXqrjUylQBMeDeJXHCMyutAJA/9AykdWGcNs7FTovBrx+hxrvCF4VOkhtdF6rs65BhK5K2ArZjuWKbdlOsVNU5EWuh9rsm34jfWVndDvSa+0ZUfJTviT+wrOiTALag2ZChVEV+8JqK6EX9lgj5YGli2NYgNSy7rP5K2hKA7AXbcUvUhFWzXz7cZXWYSD8F2QmAiGFAuZiyhQJuUS5eZQVx4M2YsFyffQe5Y9igqQz/JaYanIhQloVI1pojrncTJQTOX+mKxbQaURnawUcxSnW8nGvE+345y0LREBgdL9BbFBijaGlOIDPikUaNkamuSuwMYb36cp9kZvLnZS7XmuPnBMvNXJCgUaf0Zg3VkgQjI+CCbGbTbyIkFPXmflY3a2cgGf1YrlsV8RQS7ggvmJQC/5GOfPWQPTmt22nugorN76p4neYZtg0v+g8H6d0POdbXraCFpkbaF74KqKK/AVv8D4c5QbuS30Obl8hc/2vMGisr1t0DXbPYGVY+akPh7bYvqOUrwvWTBCR+ZscNDjZtkKJwi/3i9QtCNOWwS+Obo2YCui7Uks4FqxfHvDg5tPDI3Vi9MG+eDcfl176cO8FKvMSNUct7hsAF7ch0PT8HPABNBVsWS2Xh6FYGLO3e2bwBQq6Q2H9jMpDs8coiPwRzx5trJJEahjWTsCh0M8cvMqp/BiXQgpp19PsPHdwrQrUpMt1EtJ/DnnAi5t03ChbnI7+jJxP0IbiwA8xstOm+oIOobKHHJGipQwb8Zo2eeC+xXYSqCp8F7jryuul96bhVvQZGyx/2fYIQZEpQrnXcQIVy8WI9QNHeGSLd3rqKHvwxIWgVVeBMIiWh+hJgFkld15uUIvq+Mcvqcm7qxaqDsVYgsHtHyFsSDS3AhIh62lnxVmrYjLH1n5YUIHpN2sFyprDrI+bYfqGOehNas8fIuAvuPC7pIo+ZY60CFnagJ75c9zuI6bt5Y0HAmiZzxiYRfy6j+QQYzCqc5gKFzkzuQmj07mxWDLJAjXsuH0NPqF2WglviRVUeU3yavqTIEVSIMicPq3JA6s9zSVcpxrQpuaSEUzZ+olh2vrEJ47PrE9IjAb+RTIn4YLtgrzDyZjpf9wk0ug8EN2M5oSfFqdatHlb8MNafYqPiSJ3XauXjAcE4m9s8qWfOn4fu43KnpE+kx7+mmkwO1G0n0UA//SkKs6d1mMSp98deVIFxvcka2soXTnhLyiQyp8xyKsBGjXafTJbo2uoxokKwpIw7jzw1RalKs65M8bJ7jdy2a2XwNfr19QoAwgegJWrxrE5/+RcOgM4Q7Hq4vd6Ug9ZbKnQxJs1TvVR4bMpKqYDN9zRTE/Ol7mieOp0n019Ku5Hele9g/71KXTK+cfjDEOzyHc6LAKTx4bfPtDyRwdzxRetIAcJdI5/2YbKSJjRko9wD5AAU1I6sB2wBYLBgFmKWystypNY1RvvYLwXjdjLWzChGsug7GErFeH3CgKMrPdzjNW1N8ZtuJsC/9nP5oNFjDMur37u/tDjLG/YgbcjaykkBxa1RP9NGJLPnCI7ysDmpYyuPm0Ox4/B/Ko4f1dLW+8gaUu8mGdHwt9Hb0qJF8+6TsJWxdeiou6/qZU+AyiVkIx9GOadsN+fQHmlgVMDYD4FlOCii+nwM1eh/XCAQtv2e31nA11CZ4bmpHBGF5VdmTaIkleOg+KOiE0akVmnZBaq6bSTfedEmObIKQpcq+OZydq69XQfMFOq9S9D8JR30KVNYgqPVmFEY92WhSsfwiyzCAHHzL6LMJAm42sIj56csNQDy3wnxfQDfvDabE5qRyWddpi95N8Herc10pgUzFGpst1ROqNxzZiRwJOapFS4+vekeofnQCppkUi4SXBUbX7BF4XC9jnneapoxYyyKEzhkv/VWxYeB8RcKguwdHhCP1brvBkKp7IFZKQVTrjfWrNvuiQYpnaDFpNfljLQ4AQEsJrJ4O+uzcGs0de0WasqloynDnJqYll4+H1gYNgsQu2FEGBKHDJ9z8Jt6+KEqaqhBAO0IE9GbmUk54VHioSN1UkYohCY6rMDTe16lq3Mc5C7B+HObLxPNPfu00cnvGffDgL1kW0XWkylq7B+1DviHBXt40R8K2aNNAgmSCtLB8UX7jTFhAWoaUFmb5SBZOKJrdOo3MbD41yPMihBeSDUg8hIx0RBhRXi7nePgOfbdijJ3fSZsbmiwTkfENm5gbhXdQPq5mk9AMikIfw6OdK7U41jc8jm2GcRh/xqYzpQ7OkoI0/9dtas3kd3KIft/4ZDH1phrHmNSThZNFuUDfmJED+5CaU6GrMTJeMaXZn95+bvfkAP8jCiGia2/XGBlbzzP6lGmxitF+8lZ2c1VxqeVIBc5RAw9t85FQS9Drw+V5oyZ8gHWWYwBTnK/90JIOrtlpE9qWgfbrnxcbdxdUUapev9PTH0JnhYcXBm6pynVZ+UHISDwymiB32FbqcSQaMkVE51PlRv4UDb3VbXM6mz1KOhJN1Klj7CA0htZiHWwHCIGjPwB9pVuFeufrmukm+DP1KJiNKzPOm+nyeoe8x6OYgcA5SB4WxpfSkb5pAFtEgKkFADabROnPy/SdiX1Jlb1sdHSXIh4WGtSs5ELqhG886iIu5jMxGYFFmVoj2i+62Rd3g+TJh8aE8KEfePYgXMzm9pomBQO0oXwz8+v9UG9utYieaj0bWCDuuaUlG67bp0Tjgj33F1qiX07Xdp0AcMukGr5RLo3bQhV5vkGjPFgkmqdu9q+BWjoTSuyC00t0ll2bDCypI+bU64smeQ+Ek89lw4D1iCHZrtagwelQZPWpAbTpPLDg4nIBA6UBqY5KciAubAQ/1K0BdUfYTGnAyWS4qmBZz9OwHEZU1qfhuRi+AWPW98SXDsl34s4jSBRwfrsz138f5G495kekkOAZ/gaP0IePIjABqnjl/Jys75PNg0wlBHV8OXZXDAVqqAJXfKA4uzvWUrwd6BGCQpEbAcWiymCHaD6eZEByXcPS3y8R4qfYVrFC+vCVuZIrNLOLfvXcj5fgsz/PIqJIg67z1qtYfSzkaPidzWn8XHHVD7DgF2RtG6QcQS1K2iSelpxcuffLEEYufQyVJJUb6+L7Eq21KBCGSoGTPY+Wl/pHtNhiIywCR/1eNOcJAXLSft30n3+wxYM2LKzemkqQelpoe+/36DLDU1Xv86D8OTiMqdo7/YGDm2c9qpip3eR9aI+mDS7iVZ3fw9wc+6qP1UX9K9g91cw3mnJOZrBpAWMfn1abtFshzLXXAB32itFpOJrhAtEW5JWyjKedRSdpBjrJA5t30dyESmAr/eKmnNO9ZOuN+Zgzi4WdDu3uBo2VYntKmGoItcpNFm2sudXec66j50I1l3i17VUCqdxR40tCooB7C7CvnNj4NNkyJaUqdSIJJ0iLCRW608p4TNhKbf7ESJurRxBwQMLfAizltIExFdIZUMAOVUeVAuX4Y/+6oWLOekR4w9YEGPGclR15BuiHGEPR46l6pVBBanC14CWGkUDpWUf1mnqTtCGUtTESuc6IImTrW9e0DqTZghdmXXK50LWGREniJsgWnSd7ZqHAxEimqH/vAkzmnCngCTXCTO1Yj6aXaTsZdVnKBy447BDB+1nEAKv4ff6Sh7bJrediyRvZcaGolG1a8zXkvu4c3vbgmMJz3bjcTIh8oCndsH68OO6m7TbXFbTeHhoR4LgpAUAsjCOf7nBIbCDsPrZi3OqmVa/vLLLmyRNIlbLXo97/Yy/boVME97pZs8/zO0F4jrh2aey582NNjQny2Dyh8EHVbC3OcxROVDLI6TEIN/TYVtnQLNXhmbURGR/SSq5IRoOdhd0/gufEfrYlECQusr03uBbxxOuQik/KQ+cboA/3wGGFDZtKWx38zK6en6F2vk++pev5K+/xhGNtOWuu+UnxEMq57ggKkMhOGhmkd0hNNxrmTYkjbmqSnAM0Sv4X4KJkIZAmOdO3+fMfI9aZd3zSJmtrQi2shCrL/d7TW38c4LfvM3QgdT/vvbXV6urp/ppbesZBiEAOMJxIIhdIfF5KoAnHuk/1xopsH6d8AMNSA5YoSV0ZkbGi9PJxx7+uusfpF7tGqn8uRPNvGGtecxHKKD2SxGV4K/qu0rE7sxhCWzJvszyfijMES6EsUpOsJqXdqT0BQv+w3bzOHUTDCEyDpjDgimjh5XLzI8Bygrh2s6+Es8XvTVenzne2R3A7y0TTkXABS0nftox6OGDz0N/p9u4C8G2hwH34c3JZVFVoAs3kp9CwBO1MF5wTBRi9dwh0ajL3TpXf9nbPiqL7J1XhyFJcuS9lVse1HwMtOtjSlx+o+qn9Mp6xJgGT/5NTFn9MbJU4nu2BeeQZITYpgtzwqykgVnWlblo6gcLKAtoHb1fiGDD0hf0qx7Vhp5Vjnixvuj+sOS7CeVo08FYZgpo6mbycXzdpuadDOlccSev88p3VMlf2pmkIaoL8ZuY4S02CmJcQBMgHcyjbTe1fvJ1zjpph7h121Z3Yx8m/QGXZG2SOW6+LjeU157Yk8cOu4LrT9T3KM82YVWAZ4GvQU2VxNe6qd5U4qzLyo8TwFj2fuZjFi7HRSj2cAMfj2vae5vKXyD83ZB9yV0QgleMnBlpgrMpVMAt7NUNYQnfCxS3+RQjyhOqetIE9aXKkmVNhaiIfFOsLXvzv7A9ik8Ua/9gOlo+3kS+9lpF443ulKbKVP5+ly7RhYnNkFTCSnbz+DYOzxzf3plnLI5euV1dzj6Gp63osKxqL0vWY9zMAv+m8Xf6aKdAnIPdQyDaik2VglwNGVQFNL+xFmSJBPyRAL6OCI8CDVb08YrEPoC6j3iUglDe6A+chEvT7AxEBVn6WvVwvxD2QERL+i3PVoBkN0/r3rB4uKHesi7FXAnzJLxv7lSaWhBy9j10N/BLqxmd44GLMGzb40SKjMzYcd+Nia4WJWFrUviAIZ+JrPtcO8FqEllqIpyQc47P5D7Etgt1W+e8MDigcRbCr7esn48hLkAJjuQsDIcj0duPD1Z9o7C/KmWzqrXale90pg060F+abBx65xZtsMw3DUlAB/kwkJKcazNVn0ssn8lh1OCT1AGGORDbIuN48dwdJ7QmOrziQHUfpviKQ/lPQARpVQiSmTxAVW23axLU8pnpJb7N9cmIx5a9ethiXUheO/G/I+6wkdfwzn1IHstgUS/bcs8sSHlfSmwcwyMx3VccVUk2NfjQZX5UdzSZv8zrK9weibnC5NzT5qJBr/CdK2TZdwyW3cFTPCGThzIx3HCqUpogBSqQsvvvisWagLpwdmBneu36Adzw8EcqWu+KpAOxnpqCSmLkPmN29s0pbOzZygQ/enYJPZm8ws4DVWsu6z9D3xX9DOEkdlKThLwLaPpm1DumaGt1NAJPYoYWftMpdO/oG7zo3ISwtHH27sGqbi5oBWw9hmaSzWVTjjPXLMLpj/DPmgichGv3Lb6hdBbgaVjZDjpiu0
*/