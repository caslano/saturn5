//  (C) Copyright R.W. Grosse-Kunstleve 2002.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PYTHON_OBJECT_PICKLE_SUPPORT_RWGK20020603_HPP
# define BOOST_PYTHON_OBJECT_PICKLE_SUPPORT_RWGK20020603_HPP

# include <boost/python/detail/prefix.hpp>

namespace boost { namespace python {

namespace api
{
  class object;
}
using api::object;
class tuple;

BOOST_PYTHON_DECL object const& make_instance_reduce_function();

struct pickle_suite;

namespace error_messages {

  template <class T>
  struct missing_pickle_suite_function_or_incorrect_signature {};

  inline void must_be_derived_from_pickle_suite(pickle_suite const&) {}
}

namespace detail { struct pickle_suite_registration; }

struct pickle_suite
{
  private:
    struct inaccessible {};
    friend struct detail::pickle_suite_registration;
  public:
    static inaccessible* getinitargs() { return 0; }
    static inaccessible* getstate() { return 0; }
    static inaccessible* setstate() { return 0; }
    static bool getstate_manages_dict() { return false; }
};

namespace detail {

  struct pickle_suite_registration
  {
    typedef pickle_suite::inaccessible inaccessible;

    template <class Class_, class Tgetinitargs>
    static
    void
    register_(
      Class_& cl,
      tuple (*getinitargs_fn)(Tgetinitargs),
      inaccessible* (* /*getstate_fn*/)(),
      inaccessible* (* /*setstate_fn*/)(),
      bool)
    {
      cl.enable_pickling_(false);
      cl.def("__getinitargs__", getinitargs_fn);
    }

    template <class Class_,
              class Rgetstate, class Tgetstate,
              class Tsetstate, class Ttuple>
    static
    void
    register_(
      Class_& cl,
      inaccessible* (* /*getinitargs_fn*/)(),
      Rgetstate (*getstate_fn)(Tgetstate),
      void (*setstate_fn)(Tsetstate, Ttuple),
      bool getstate_manages_dict)
    {
      cl.enable_pickling_(getstate_manages_dict);
      cl.def("__getstate__", getstate_fn);
      cl.def("__setstate__", setstate_fn);
    }

    template <class Class_,
              class Tgetinitargs,
              class Rgetstate, class Tgetstate,
              class Tsetstate, class Ttuple>
    static
    void
    register_(
      Class_& cl,
      tuple (*getinitargs_fn)(Tgetinitargs),
      Rgetstate (*getstate_fn)(Tgetstate),
      void (*setstate_fn)(Tsetstate, Ttuple),
      bool getstate_manages_dict)
    {
      cl.enable_pickling_(getstate_manages_dict);
      cl.def("__getinitargs__", getinitargs_fn);
      cl.def("__getstate__", getstate_fn);
      cl.def("__setstate__", setstate_fn);
    }

    template <class Class_>
    static
    void
    register_(
      Class_&,
      ...)
    {
      typedef typename
        error_messages::missing_pickle_suite_function_or_incorrect_signature<
          Class_>::error_type error_type BOOST_ATTRIBUTE_UNUSED;
    }
  };

  template <typename PickleSuiteType>
  struct pickle_suite_finalize
  : PickleSuiteType,
    pickle_suite_registration
  {};

} // namespace detail

}} // namespace boost::python

#endif // BOOST_PYTHON_OBJECT_PICKLE_SUPPORT_RWGK20020603_HPP

/* pickle_support.hpp
kKLzvjphkBpEO5XlKzmkYkQJqzsg1K46ZY37zTpaKqmLDBUikf49qQPInN1wt2N1Igoj4K6hTPzKCTvFzdxcOYSaApY+e9rU424JFCZf/BOF/4BqGzOGnNrmmdhFXo66rNzbpRkpNYeewf76i85gryHzOe+sKs5maaoAElfA2JM2YrRuYpBEg9+xtt4PyiIPCyz6penkF6xF+u4IvX7dAT+GzojX3Px96wb6fFZmlJo7qBQpSBqvXnLOKV5MlKc7H8IsRmqcv0hbDoCJYJiT254KITj4zd8RTc1uZbRNh9YLRbPNW5oaUxRvxW1JrDa+mMEMlAgiGPQbQatGLx9GmnaJUQhXmSheWF0yA9Yi/walCJfwg5ECUliF0vhrZIGf3FL8ZHYUZ0y49G8KlI9OeWkREb+kKsQyabtifhBNSsaJxYEmkX/VMm97gqKgQVb5RAPAINdEX2LAyEOiDZxrU2tRaQ3QyU5ECtlRXP+P7qAkIOlS5+JhTtEujGKUSALfzA5ljMwo/20zFdP+4RgzQ2uaG2Vud1IPREaJexbSxhwhzyxnb10RjJylEcIkbOrLkrRkklc25ZuhcOZT84wohvRvkjACeBg95gQqaBly9qok4VBtYA5Kj4Ca0zkUTJp7mKIdU1mTE+Vh0LwFlQ8LA7lEkVxYJ6u5O0vYIOKCnv1pLbhHVBMytUge1u8efsgKkTLxQywxK3wW8VZQbRIknTo3pYhfks84jx42cdRKpAoIvzO2mKPABmA+M3LMhcpRkeAoHuXqipUo+yiRsczIRl6NA5JptdPp4qwjaJUKkB6LE/xr1OmOhVx6QccNv2r9hHmUbDmAg6gnU1YtSMMiweVgg4GOylmcKPXwWlucalYdqR5+wQVRtpHm/NGjpCwP+2tHeVDMvoiYLmAAk3ASks7KZQc8bjoaBa8oEFeONkfdFy2XxhauFZnL/C5LLOSkyhSeEaUtVQS83HLChUiELBwf+5f+8NJvUhz6H5M2Htmdj888KAEkISnV4v2sy3aJjwW1Lpc0P5sHVSE1M6X5r8bRyikHDXtOYKK3Ncw2KgDeOBkkC4C6N/6t6svLnE6iLp+hVDeSImj+KJcalmnA1btUXvyeMmqu5jOPGZdmH4VfyBej0WtpiNcWB5fEGtRC0uDiahoh3OI3FaKBRENHrviTV7LqenMBTMU10q/X37PYqMGJFbW7hZ1nJsOmKCfBuPEn1kP3X9TtSEcBdGPsZ0mpgQ2epiug/E+E8xOzOf9spBuIloDYq6ZmzqlZ0MGCzEaMQPsCaZXlCrnv8GN6WlAz+T2GUVyglQqrerxZizpIDh89WOeHAAu9Erk5Z6h7aP5YFCIkh7P9bUGFf3wsPFZoJ9l38UqYIbH84i2K61cdrYhYptZIKWxtB2kLNn9J8FW4MeGKALetSC50lv2BHVFH2seJDjHsk4fyGBUS5SSFmdD7tzI1ugYTg2JshogBTBahqB5A+VuDT4EyWXt6GTtPkCWRKaC0dJDRjixtNPlFJEgefB6Ge6hRP2Vaa0TiiHG1A/Y30Awh7F+I3F0NgX/JQqQSCZRMFKZ3FPGGjDzzzrEmpnVEYivvNfuqHUh2xJz5JN6onNYQi79HEIr+dunHenFjNPT+1k3OI5FXnbdEH1LWH0Qkm8gRL1GEJ5fMK3Xiw6pKECkrvKg4TtqAolXCFDRtwunoPBCSYhPpG8fl45Ce87jkPkWyQ/gVlzQ/55fV4R6JkBHMPxQJ0X/S+v7bE9OJMubElSHJK2DN144KYc4Ak4g4nU65hXeaRhVTe86mxlmSrI4xJkBPBWyD7/IuM1tIjNydGTZCWwKnM5ZVY+141bhP8BI4l/Be0BjYPSSZrN/vcnI00V9RMUVrFyjVVD9lflRBfEmCoEGRSE8pgcyZpNhzlIR0Vdu8rj8IQfV+ItJJdMfZCKdVhIl3lH7/BTOKOFaCIjIpRJjg75dtxrgRZ64rvaHnvcxfXcKwy3sOkmAEjtHR3aSAl8PfTO9xKhBIAW8ZwQ3pBRsQIpAGNQaEzgNZLm0m1pTfXHlQFLIWSH6uUrOfnqBP1An+LIJ1v5ih8dZXKRvqJZT6UylvQBcQrc9plG6oBU9GDs0Sd5B/YRqRjSnMUcCFxOFNTVjE3WRVl0IwzQP/bh2TX37ugQ7mxS+pGO8qAOv8wwUQwfo1g+JOyU8kjjOL1rh4zK6gZC65e8+ZJ9+QJNKsoK2JU+n8nZaEW6hM4gthspEWNDqn3Nfuh4FGA1wi1PJ7H3LAGYdCUQlqJ5KKVbK2uy9l7S82CuMYECkToa3aYyRxLiib0XJAvh+ooqJseWSZMyiZhwh0XFzNLLBoEUECQhihCqKNPSwVziKUeimFdhSBAVGVAvaKnYbRnysfNi42hRF0/5wDM/48Cm0gWjAiH5Mt5vbz5mfVUV5WfCV9MUItrmEWeyAYyGx6MNbRhpyJ0WvqUvbRi8MyUOnVqdNjAf14oiAERHz7EW4wVnht6rZ7OCbfeugNAn5D3/wVRIgUo1Itwoux2v+PQ3sIDoTRAQBc29jatrm1bbtb27Zt27Zt27Zt+/V/h28mh9xySDJJBCf6MxsoWYN6Gr5hbewSyAvjGnYWsEYiLAei6jGOPfj0SShYLvqiL8AEgh/GsA3zVKBcNgkmEanvsOCt/Dzw21knwXjOurBQHjqXcsOJQVqBIjndpQikcPEsptgpMVQJGJqQkLfACP0qvj67G6Q7TRg2fxq9NzGDgOnwpl5DH/ZL0fAjeQAqNzY9SmIDRnIOetD+J+7oRAKJTKIxZgljL8bf2CSbifZM4AjvYoXarmxQdi0966uDSV/igbcu8jjghrxyNQHTIrEqzOo0RsYLFSgO6/xyihEYdt5zrBJ66rMN9aOz8Dmws6EJRBHheUzNEBfboNlYzWoEB1IHnYeJEcpDgLg4zDkx0uTLGYMcrYmFA6fH3mUZov7O5izqKPJmp/74vJhhQ0P6pAUxw8hUvICAQww951v64HQ7VIrpWg1poWg90zmhGKYjJiYSxtQjrix4yuTYPjl9qDAUPhPmP4DjzGtu0BV6xMiHAsIoXPzj4XrkjY0GetiIMDHN0Wxk5eNu+eSjhoECuuXvc6Zm1YfXBURm0bg9rYL4f1aDlCCfD6P7eTrCEVngkCaYqZXO+lXR86dlITFgnIYnWbPJ1gEyqAHqL7Dm08QKtPUZWVGdV9WlmRT0IgWMjv/s93uHQ8EpYLATAonc5ZsWqGlTOz2CYPN4CG367ZvSlyVQKagvIOkXIiwRjo+huFmAiUtCpPxbXjBz0ePB0ueXEeuln5REtMvHrUVbhQ0Y5VuUMsTOykxQTANuITyc8tsVeefn134PjB9cbUAx4Hlsz7Zbh8CBYjhz7m0kPz9FQ5AnZoYJa0X0HTakyhZl9qU0JR9jMjLKFGim+z4nZpqqtHswKoml43ifLp4hofittvGGXjSGzVkLfdpbqCqdeZ5EsLEO+h6CkBEiywHCIJcvqKueIVBCZFhx7LnKGz/l4nIcucDsntIhiTub+Z+itUZAqc5739xmBwnQmPIQJuAxUPcpAgUPT3w/K9stW8NxE6tyGIIZgtMryMz8xhVUclsyk1jaeE5MI/+qqMJQkahIwaZnc+3RMKIcq1qtxdjMSlSMZ6UqLmi0U9/qSQB6d2NnFbMHCft2OUNGTPb3L0AeMGz3d5WoAWMl2HAOROZ+M/I9nLjYyFTav+uL9Jd2+iq+SvHKiiFQ0uO00uOUiUKHalgstOmepnD8++Rb8BWg0QK05W3WpBqSOgF6nGVnzLyR924yLHdv/gM2Nm1/UOQYUHnaaP+4E2NNrP20mqRMSDVlgaRFlbYHySO2SR3yP5NGABVeBw4eetcYxdEz6oHwOfVPFsP9UzqisoMIlIZqGgqv9UaWqp6wtE8bFWyyDsvwbxmUNkRRx0UFwi5mflNNFGSM/TDbCzggDR7RAZviY5zgy60JgOu4IQOp3qXNRyNdDKMnwJcsAGudoI0TmX8iROGgGFTG6zeMvrQHiagESB5UMzLmaZ+dRGGSyBeAhwbiLnh22To2Wx6bRmRhjOQkDed37qjK4hGKNTtzG0jNHb7WGQprnRkWQBwGgVh1srpkkv6j6BzXBhIUapY5v61n9pfxwFv9IItPryLhJABgdDAfww59ML0kiz+NU/LKoEyBPkRdGh+VnX1Ojz9m1MEAn5RDa4C9bIR4oPoigZYC1EPmjhniIUORMwGoTS2FkiRHct1QYjYAMApJErHf5wganVCmAslVNU2koJlCPMFYIq70rrVEvGt5bVWIVEq1r47bDZIS2DByrEh1/etHnWDj8W1btq2w03mxBr+gfPGSJ30ysiweAz4+O06biIOEjTfOV6jysdvxnf6JXrtAyZVpEKk9Y2GNRWIVUhMVBVQSmwBRePViXkGRhKhsGXijuBTNX1qUKhOSfrEVzyj0SAJpEC71MLBBzgYEhDZ1EFXKCOucAWGhCEmIWvAxOBpVwL9AzZRVnTzsKEPIjoVNo55EDMHZkFYXzjFtcbSmXU26848K7YFc+qwo3Goe+MnleRoaRSrhmke+InuaqK93LYVSRnsn5SgjUy3NjEoGqUqN2oowSJ4ZbRQYQIVpBpSbXjpmosTIJnZgjbx7b5IqlOdWuOltmTreFlaTJBeYnqXbatqYASFnm86uhO+CMkaWVfWhQ6SpbeK/lQ9xqFDOaCC1LpyDdHrv2ny2+PtxZrFaAvRqy24YCnHUydV9wAawiTI0zbROZ7xiwsaox3liAMkN3EnmYju5oloaiR6NBbwgRGfp6tY2paFYRZIQ7POlqwDv+DlWkepyhvhSztTxYImEsSMRaxXSZH3Wf3YW9ZT8LASzj+sX3Fh1s4IsjmtBAqVSuBDp+w+kFEPyU+3AHBnJlLHW6v7rajGzgmTa2WrBSIQsAmaiCP2cQvKYE/DIgSNsaJsUHblWG+sOWokqaBVamwQNNdQ26691KSNKoXqMC2wkdgy4ZP34jHH4upMB092+2Mm7ofpFSHQApFHuZ5TXy3LrS9fvZxdab/RoIfgK7EbSB32BfijFdIIRcs5nwg/1QALQFSIRF/puV8aNMTXE1INs1anGdu+csanYd5K81jVmyYSSsw4WHEVJZE2vcR0N7bKD+rNzQ0jK6shU7Pp/EFXq0lkMx8/T6DNkS8FNrN4pk9d3EbDgY2/GlACMt4EZBZlV53XALUQg+gESxOg/ARvppKbRSUr7kJnDR1Ita3q0k9/oWZCI/yRsuosg+Y16rJfYCR1Jhb5EyhOOI74FamqRMHFnYTdKyURhLg9rQrUpWJMOwwEwYAJVIDezVGpbB+LTv7ml6TsQxDRZZktbnlJ7mWnlwSD8U3JNsgf1qYPVIjuhLiz20I94VDS6kiRcHA3oWfijUCCeQ3z8wnxsWUy3tOZTqhwJiuqFn+0c8miGDGkMA2RBKu7GGV6LQL/7OvlPizgM8xEZem3WogvfBByRwy21X26Sz86vah+SBul4rRybG55CEQHdYg8EPnB8Lg7YisksWjA2sF93H5P8/nmU2jRshp9FuDwmvd8kDH8q6J0EwqTfEQHiL5xHDPGhAGljmhpFTHooqf+t3I3A0AB/ShOSBSvL19t8Zmtd0UOqZOjlaA1Kghb7Ctx0e3503m2Movy9aUdTnOKkAKi+qMzbaC2j9KUxMBRIXnAs3ztqjG3H6lu2tm9oyA+lcgtTMk0MuT3EKi3qY1ho5ohxi1G+mhiLQgBFKWt59akdMxUBIHzX+x9IA/2JfLl4fpKHJEC859KYc7Ex1XMJEiE1eHHf7y80Ozx0FVvEM2rPDZF0uQsqnbxjDCtIHxLqQBvPfH/tjgl4a9Aba6f1dDyfPGm2baYI9hXZ4gFnDYqYtHbnfv3qwcO1WSaiuieJK/ilIxHcf+LhjKjQ2cBm5rup2JwNSIX64Kx/TLYhSaBAWQXziyxMJMqVhx9lMihSA3aQFuqFM7nEy5vtozrCQ+uSRMzOJ/QdB1Qj2AiR5WuglzybLoU8sYY8F0lSqRQnUtB9HVS8Q/oiCqpSm9dO528IIaEF7JskB0XqqyPwoY+PJvgB4uIPJbmf6yMOizCJ4oen3/H/zYpWZ/LWjpKriwVRurVJdfwzIIUv3aDOm2PUkSsqVmdRmpsgMVeRPG1WxUljXK3jfjsL3x1BZD7LTjK8HFGom8Djo3cmn+HIuzDoMuxU+ldjzY1ubr9SefHvSlNNBHhqeCwFo16e5UKJOb9EouDuntKKPJCoJ8XvSUwgsF+U3k9g1RFENcb4FFBnGr6YnmpzHubvQD245SYt+yxbHVuA5wUkMGqzsMJayvHis3Te6vyudRh9GJIBwqX16lDqpItKElcb/MbHauBJDX4qj/0qYB/7xWwCdMb4Iw2wuoV4pXSnTn3sUoKV3Qw/WeOmLNfVsHsZM/aqchRbrpIjHPbJWwrnkLrQHRRkvgteJJn4MHJ9YzLaSLBt2FOHPgGQHfI+V/EOBsnOQC9gan1iVOctKXQQiwcKsoeTOa7quDxu5UaXPmXGx+NR9ABHcOupqhECsJuCGYjp5tNx4VQYSiX5B5E06giRttgyqyADd+lU00BNIkQL1RQKdp1Lv18Qd1ABGjJ1VFCRf1ZjhIy698bQ7VoREAfNbSwdaeatmz4XacSBnYoEmL077iRhNPUBSlY9uPtw/sCAPjP1rcPxS4K5r9s0EPVw1WAg9T6W+r4RGGqdMANnZBLgCF82BMFaCa25UkIVklC7M3+17aRYdylgKzkhILfw6vQbairI89uQfyRxBD5QlDsU30WwYqCglBKJ4+iwa87FEYreMg1HAGp+SwI9UcgcfZf/KHiFtJ/q2z2TEqaDLWgkS2ZaR6puKWFDouxF4ghZoPE6qhgDDUarby6ILnCvMOhkK5iUxjgYRES4ewCcWEK0aI/LZDH7gW5wJ6CFXeNkj1xvBWPV7GDwvGQL/FQ3UaYcrO+acOlMTwxJDEwcSX2I3eSnlJX+ZZcjwLSOYjjzNsGBhSZK17JLW/9xMyLe5Xkv5gzbHHnRWEomQ7Kwo6qkM0MOS8Kgl2ovGBXAfrnhNhY2KrKQbKo6EQoyoYkhEh1p4h/T2HKd8zCjFFuIePr8vHppQ/t18tUlX+pR30mpzJC2mUlWork3SWts/8fDe0fGjDaQxLTu8FAEN2ktt6aIp9DG970Ewr6KKNf13BayTGrzGHfzvnMoTWXRONCg9j44oUcDT8sz+b4o0In9PA4mogl+HcrOcNXJTSFx5JJ5WtRiNYLNBKI0PzNd9NghxSu3Wik7FEXY/djT8FuFsPa5Ws+ggqGg5UDvB+llVKd//foRkKTH/zDi6a/o8+Vlez4RJZUwWuCwAglKSFlNpapKmzi4vsvV4y7Y1vd5hJwTDlkozD35NnOxifzPA+bctlLVLkqYwUso+zrz6ZYcy+otppn8hejwnuJR5JJKBxrjSVZ3Syxn+vQRvnLuXWkHv9IH9884p9jFMiSQ8l3Y9VWwl/9kXBFucM1UWw3EydXDhmtnSTJdyiiuCjv6wfDRte+picc4KyHmolLRBRwGpuBR9RGEdsPANCLIYSAY3CEkBCOL+LG0lJpbwegooCBOkYZSMqGWPc/CDxbo
*/