// Copyright 2005 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 3. MPI Point-to-point
#ifndef BOOST_MPI_DETAIL_POINT_TO_POINT_HPP
#define BOOST_MPI_DETAIL_POINT_TO_POINT_HPP

// For (de-)serializing sends and receives
#include <boost/mpi/config.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>

namespace boost { namespace mpi {

class request;
class communicator;

namespace detail {

/** Sends a packed archive using MPI_Send. */
BOOST_MPI_DECL void
packed_archive_send(communicator const& comm, int dest, int tag,
                    const packed_oarchive& ar);

/** Sends a packed archive using MPI_Isend.
 *
 * This routine may split sends into multiple packets. The MPI_Request
 * for each packet will be placed into the out_requests array, up to
 * num_out_requests packets. The number of packets sent will be
 * returned from the function.
 */
BOOST_MPI_DECL request
packed_archive_isend(communicator const& comm, int dest, int tag,
                     const packed_oarchive& ar);

/**
 * \overload
 */
BOOST_MPI_DECL request
packed_archive_isend(communicator const& comm, int dest, int tag,
                     const packed_iarchive& ar);

/** Receives a packed archive using MPI_Recv. */
BOOST_MPI_DECL void
packed_archive_recv(communicator const& comm, int source, int tag, packed_iarchive& ar,
                    MPI_Status& status);

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_POINT_TO_POINT_HPP

/* point_to_point.hpp
p4v2KJ3M17lFXNcPgCZyqvimhwdAR8jDmzZ2kjOuUEeF31qAK3fIH7ieReOUbpjCf05T+IydIElsGbQXlmaGfNAuXns3Yu8kFJb6KZn7coMkY5P8hvX/FUt3iz/fbY3E2JtFO2Une6yep7wuzhTGkS7XjH6B23VPUT9NoJ4a84ZohN/niT/zMSfhsx8w+qf2U1vvWbgKzzL2DJVGUAhM62d/mnss9OOB/qMmQc+cKPFmKQBjqIipBa9eiV5bKlFqs8vVVRgLg0VuMrL85PIL/vCaHMZfwLLHindmvKflZCocJvoEHrJaMQGtuKwpIocuWC+NrdtvKjERTuV2OKgSR24etYkL2A4zsbFpAeXUxy3aquXQFj/6k91rJ6z9hrVFrI+yy533wFp7eOdhge2PjV8rogsrd2/9iCy9CovOJ+n1VFKcWMiIf3xeVPxD53pM97KXehk258TrX1LGE5cUYiX/V16vnqtJvno7ett5R9sxJR2mjJ5xtFhZYSxIIlnU2XvIzsMNQsYiQtQ71W2mqZB1JH21PQrpH7FHFNGOTOfmeOdB0Nq/v5rwPMgnmwnB4cVZ2LfLAkRs/7zLIr7ay4xxKnMiIy2FagEf+pq1g8rVNZCGBvcUXUzXi8D4sbpf8KrAEiLrQOS1voZa+rjpi9muN0chTeQL6GgHWX2cX5SJL8LbcDpZKPYRVDgE+wnBVJW2HhhlsuMlNuhEm5TFhSJZL85+Iq+m5V2NwqsA545Wp8sr5DzajGJ55En/vF1HQbk6WOD0wRKvow4/XXHRJlhu1FigfDfRaqeLp0+6/mOOd9FwrkTesQsOvxxRFviiESQYppKhmScuvDcWPocTMpGQiQSfIEi8/zp0CgUodVWlqQKiobv4ZSn9iV9I6FE0liG0l/Ch3uSP+T5DkuT8hTpjpSbtxOc/yFU+OBijERyptoWde6G0MB8iOcV0+DlF3St7IKSgX+Q2T+ANcmOHleyQvItfXMr+KNeUuqqOD37fWfJSKRkcjkSI5BaQrI+Q9eap74DHTRRF2BjlGaqh3F9fkYW915MgFe5/QKtTfYJlgv4IoM8Q9C0Piw2U2bVieDhdjV9jIh2Odg0nRNhVHU6nwKztgnqqjL3Ii/jA9DlOtKte1tMWb6oyVMMIf31pFpxuhkAzIzb7dLO9rDxFIKHnncb58k4bvWBXgskNXiRVnIEqKqUKaIt3yzRv2e879i9LbNq0N/4bPcidRFt6M03zrlr0kjZHh/sikxkBmXwLFRw7OulHOkDEzSVSpFz1fWVvdkut82XEH8R4Ym8tBgv6tXSZ96atTfpw5t3A3O/FSdArJBcKq0EKaxwrZpz6SJCnopYM7Fr5UL15rO5qqV7r7Ac6KvCRfVCq11uOH+60FWejflgOZINf7168iFxpemZ9qQ9le0KbKnpRoyUfkL0xvX7J99yl5UnM/M/UqzKJA/Z43jIrvcwn+kec+VH6XTcygf8P6bey0pB7vDCTZTA7i1955xbpBzDlCtmqgWfNcGECqaMIrmeGLgnnMZTc21WqY75//YXdtBMuHn++yDq8hHso8f7Ou6SMOid9t570a4nOxb+OaecMkqee6uwAx3lwTPrLH9EHMPg7HK6hHe4Z3WNVga64a9j3PzSRfD86sJlFTo664U2nfA+NDOZYGxE3XSURsI8HLNMt+Zas/CfDO49lh6DqHR0cyGAiyQ99BkDBkykJEr+KBNv0rfvkqEfth+DPDR4uFYnvzcqNUlWObiR5X0gSVRJ3/CRdv4NMnflSzn73xrxnxrz7Y96TY96z6T3+fKzPf75G42Ho8Qg0R41HMfUn6N0f7G1/4fHNiQbhEHsQfrVBeiZLD8I=
*/