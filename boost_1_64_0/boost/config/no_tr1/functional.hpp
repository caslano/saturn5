//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <functional> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/functional is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_FUNCTIONAL
#  define BOOST_CONFIG_FUNCTIONAL

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#  include <functional>

#  ifdef BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#endif

/* functional.hpp
HLgB336fi3uNlFaUcpBhYDLiiQ4LiluQjyNkQ6Mm/dHi2wt2N8d3P4CbD0pnqYViy+NHB8VzyEUr2bB4cmgVZtAweWUW8NTRyhwlpX3HhnHehy0IisuQjyNlw5MfHbNE9/aAtc3Q/hvg3jeIw/b/A8nk9z0tKNzIiZK9nnrIh/kaz4apQayd4uGeI3HKSBMbxmkPPTNoZNOjLNn0LDgc8BezhGjMykdVVCZfJatPWgfIWTdBcuJFTo5Wc2TZUxvxrWE2ZueZzS6HVYcHl9EF5/0bjonL6h00dY2PUXFZbS/HOJQzwZe6T86qy1UPVlGl5YRK/r/hmLj2C9N8tJENNWe/erZ+4zNghQ+zprs554ccZ6Q0XhKjlk4Nji2f9k/vqceq+VF1Fcqnp8NMZCCHm48ow9xADLNOLknPi+Nkw8tlvadjhFL9zYto6ZAYuQBicGwb8WXpeXG8im9+52f0xZ8G8+ptXiTCDGQoENs2ODDNRZ5s2Lp30TW691SYXV9cxCL0coeBccT6XpleK21lw5R3Gm7TvadAvwDqcdx8xGmDXR04dgxPOD0/TpANywbN+0u/cVdYUF/zg0EIMyiZtp9ImosTZUOL7nmYL/jk+ts3qjj2DQnilM+LgyZ3svIhrM7e8ofuPQkmnYQW9SY8PqaqqoGUBjDz5y2b6PigKMJYx3by+cPEv9vo3i5wd6ruBM89axwgqUMlE8LO6TQhKA7HedBeNlyacKFs0RkWoA1wN9MdGT1I0iCmTAg7FnpSUPTHujQFsmF4+3Xoa+wEZTlo7WGKia+JDxxcWklZNd+CsGOA75P7Aq6LDkrW/HzKabq3I4xphPuCn5UHwnILFoQdA/xoUHyO66JQNmQFZvXRvYWwEe05qm5Tcz4eyunOTAsh425tULyHc6GjfC7ZW4hxnh1gB1qDlwVZ8oOmRlhJd53SINg+1peDYrRfc9BJNvTLa/2QfssCyHPjPODJcaZGGFFbOOlyyEAwa2FNULTHedBZPt++98HTk52ydXYqlxVT/EFqhKRrwSAYDuRLB8Vk3A+6yIYDNyxHeaEd9M3Bc9LNkvswOUIp6JPmVrdAnPb/d4NiFXJxkmwIzDwKvSD50AG56ObnsdvJYRJbImwEIz/KQ2AucnCybGh44g9f6rc8Eap7oAR1GEvNeDXCWFE4RpalxwA471L6QsbG31U2TG75PNawOwGmql9QvwNsayI5xCJVPKmkPBwpkr9PF9P5X3C2LOVP83OKxU9bmP5/4IcyCvi/AW2fiOTofOToVNlQu/ygy3RvHnRHOWuqi03GiBUNpovkMn8/07bbICQ+xPc/TTZ0XTvtYv2Gx8P2Q3GOeHniUZLji8jsImVlpXRGCQvF5qJZei50s+bCcRCtj7kQCdOeK2mEjLiLkIl5PV02LM1ZgRmNjoUtDfCF/Wx6hxxhSVh+tc8vileWjWxXkF9ITIgTzmnfPT4k+iA/Z8iG0aPWpzJ5wI5G+BNPzQI94Cj1uSsBnPJXYUg8jhycKRtWlK/x6t5joC9mOIkHGeeIHGIBOQkFtvzVIyTeRg66q3yhDR7A3NNHw3LcK8Zw7hWl0RjxnmkQjO3u3JDwIAdnyYY5x0/HuCQZcYGrIj+bkYOK4YQmTINg2yjOC5mceGdDZk681rA4I8dPgIuDSlrV1ABk+gDPD4kS5KCHbKg+967nde+R0AYtNjM598SqCFmeTAPg1EUGpGWHnpbs0ApKcB4M4FwLVRFS660ByLyjfmlI/I0c9JIN3/U/DmWHIyCKJ0QzyUUDRg606F8eJRYbMpH2M/f24dz5dFMjJafCKTPtHhQSbXFe9JYNp8wch7HNLY2ONS+bUcdIxGI=
*/