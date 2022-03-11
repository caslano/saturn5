//
// ssl/context.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_CONTEXT_HPP
#define BOOST_ASIO_SSL_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <string>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl/context_base.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>
#include <boost/asio/ssl/detail/openssl_init.hpp>
#include <boost/asio/ssl/detail/password_callback.hpp>
#include <boost/asio/ssl/detail/verify_callback.hpp>
#include <boost/asio/ssl/verify_mode.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

class context
  : public context_base,
    private noncopyable
{
public:
  /// The native handle type of the SSL context.
  typedef SSL_CTX* native_handle_type;

  /// Constructor.
  BOOST_ASIO_DECL explicit context(method m);

  /// Construct to take ownership of a native handle.
  BOOST_ASIO_DECL explicit context(native_handle_type native_handle);

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a context from another.
  /**
   * This constructor moves an SSL context from one object to another.
   *
   * @param other The other context object from which the move will occur.
   *
   * @note Following the move, the following operations only are valid for the
   * moved-from object:
   * @li Destruction.
   * @li As a target for move-assignment.
   */
  BOOST_ASIO_DECL context(context&& other);

  /// Move-assign a context from another.
  /**
   * This assignment operator moves an SSL context from one object to another.
   *
   * @param other The other context object from which the move will occur.
   *
   * @note Following the move, the following operations only are valid for the
   * moved-from object:
   * @li Destruction.
   * @li As a target for move-assignment.
   */
  BOOST_ASIO_DECL context& operator=(context&& other);
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  BOOST_ASIO_DECL ~context();

  /// Get the underlying implementation in the native type.
  /**
   * This function may be used to obtain the underlying implementation of the
   * context. This is intended to allow access to context functionality that is
   * not otherwise provided.
   */
  BOOST_ASIO_DECL native_handle_type native_handle();

  /// Clear options on the context.
  /**
   * This function may be used to configure the SSL options used by the context.
   *
   * @param o A bitmask of options. The available option values are defined in
   * the context_base class. The specified options, if currently enabled on the
   * context, are cleared.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_clear_options.
   */
  BOOST_ASIO_DECL void clear_options(options o);

  /// Clear options on the context.
  /**
   * This function may be used to configure the SSL options used by the context.
   *
   * @param o A bitmask of options. The available option values are defined in
   * the context_base class. The specified options, if currently enabled on the
   * context, are cleared.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_clear_options.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID clear_options(options o,
      boost::system::error_code& ec);

  /// Set options on the context.
  /**
   * This function may be used to configure the SSL options used by the context.
   *
   * @param o A bitmask of options. The available option values are defined in
   * the context_base class. The options are bitwise-ored with any existing
   * value for the options.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_set_options.
   */
  BOOST_ASIO_DECL void set_options(options o);

  /// Set options on the context.
  /**
   * This function may be used to configure the SSL options used by the context.
   *
   * @param o A bitmask of options. The available option values are defined in
   * the context_base class. The options are bitwise-ored with any existing
   * value for the options.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_set_options.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID set_options(options o,
      boost::system::error_code& ec);

  /// Set the peer verification mode.
  /**
   * This function may be used to configure the peer verification mode used by
   * the context.
   *
   * @param v A bitmask of peer verification modes. See @ref verify_mode for
   * available values.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_set_verify.
   */
  BOOST_ASIO_DECL void set_verify_mode(verify_mode v);

  /// Set the peer verification mode.
  /**
   * This function may be used to configure the peer verification mode used by
   * the context.
   *
   * @param v A bitmask of peer verification modes. See @ref verify_mode for
   * available values.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_set_verify.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID set_verify_mode(
      verify_mode v, boost::system::error_code& ec);

  /// Set the peer verification depth.
  /**
   * This function may be used to configure the maximum verification depth
   * allowed by the context.
   *
   * @param depth Maximum depth for the certificate chain verification that
   * shall be allowed.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_set_verify_depth.
   */
  BOOST_ASIO_DECL void set_verify_depth(int depth);

  /// Set the peer verification depth.
  /**
   * This function may be used to configure the maximum verification depth
   * allowed by the context.
   *
   * @param depth Maximum depth for the certificate chain verification that
   * shall be allowed.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_set_verify_depth.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID set_verify_depth(
      int depth, boost::system::error_code& ec);

  /// Set the callback used to verify peer certificates.
  /**
   * This function is used to specify a callback function that will be called
   * by the implementation when it needs to verify a peer certificate.
   *
   * @param callback The function object to be used for verifying a certificate.
   * The function signature of the handler must be:
   * @code bool verify_callback(
   *   bool preverified, // True if the certificate passed pre-verification.
   *   verify_context& ctx // The peer certificate and other context.
   * ); @endcode
   * The return value of the callback is true if the certificate has passed
   * verification, false otherwise.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_set_verify.
   */
  template <typename VerifyCallback>
  void set_verify_callback(VerifyCallback callback);

  /// Set the callback used to verify peer certificates.
  /**
   * This function is used to specify a callback function that will be called
   * by the implementation when it needs to verify a peer certificate.
   *
   * @param callback The function object to be used for verifying a certificate.
   * The function signature of the handler must be:
   * @code bool verify_callback(
   *   bool preverified, // True if the certificate passed pre-verification.
   *   verify_context& ctx // The peer certificate and other context.
   * ); @endcode
   * The return value of the callback is true if the certificate has passed
   * verification, false otherwise.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_set_verify.
   */
  template <typename VerifyCallback>
  BOOST_ASIO_SYNC_OP_VOID set_verify_callback(VerifyCallback callback,
      boost::system::error_code& ec);

  /// Load a certification authority file for performing verification.
  /**
   * This function is used to load one or more trusted certification authorities
   * from a file.
   *
   * @param filename The name of a file containing certification authority
   * certificates in PEM format.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_load_verify_locations.
   */
  BOOST_ASIO_DECL void load_verify_file(const std::string& filename);

  /// Load a certification authority file for performing verification.
  /**
   * This function is used to load the certificates for one or more trusted
   * certification authorities from a file.
   *
   * @param filename The name of a file containing certification authority
   * certificates in PEM format.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_load_verify_locations.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID load_verify_file(
      const std::string& filename, boost::system::error_code& ec);

  /// Add certification authority for performing verification.
  /**
   * This function is used to add one trusted certification authority
   * from a memory buffer.
   *
   * @param ca The buffer containing the certification authority certificate.
   * The certificate must use the PEM format.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_get_cert_store and @c X509_STORE_add_cert.
   */
  BOOST_ASIO_DECL void add_certificate_authority(const const_buffer& ca);

  /// Add certification authority for performing verification.
  /**
   * This function is used to add one trusted certification authority
   * from a memory buffer.
   *
   * @param ca The buffer containing the certification authority certificate.
   * The certificate must use the PEM format.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_get_cert_store and @c X509_STORE_add_cert.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID add_certificate_authority(
      const const_buffer& ca, boost::system::error_code& ec);

  /// Configures the context to use the default directories for finding
  /// certification authority certificates.
  /**
   * This function specifies that the context should use the default,
   * system-dependent directories for locating certification authority
   * certificates.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_set_default_verify_paths.
   */
  BOOST_ASIO_DECL void set_default_verify_paths();

  /// Configures the context to use the default directories for finding
  /// certification authority certificates.
  /**
   * This function specifies that the context should use the default,
   * system-dependent directories for locating certification authority
   * certificates.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_set_default_verify_paths.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID set_default_verify_paths(
      boost::system::error_code& ec);

  /// Add a directory containing certificate authority files to be used for
  /// performing verification.
  /**
   * This function is used to specify the name of a directory containing
   * certification authority certificates. Each file in the directory must
   * contain a single certificate. The files must be named using the subject
   * name's hash and an extension of ".0".
   *
   * @param path The name of a directory containing the certificates.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_load_verify_locations.
   */
  BOOST_ASIO_DECL void add_verify_path(const std::string& path);

  /// Add a directory containing certificate authority files to be used for
  /// performing verification.
  /**
   * This function is used to specify the name of a directory containing
   * certification authority certificates. Each file in the directory must
   * contain a single certificate. The files must be named using the subject
   * name's hash and an extension of ".0".
   *
   * @param path The name of a directory containing the certificates.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_load_verify_locations.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID add_verify_path(
      const std::string& path, boost::system::error_code& ec);

  /// Use a certificate from a memory buffer.
  /**
   * This function is used to load a certificate into the context from a buffer.
   *
   * @param certificate The buffer containing the certificate.
   *
   * @param format The certificate format (ASN.1 or PEM).
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_use_certificate or SSL_CTX_use_certificate_ASN1.
   */
  BOOST_ASIO_DECL void use_certificate(
      const const_buffer& certificate, file_format format);

  /// Use a certificate from a memory buffer.
  /**
   * This function is used to load a certificate into the context from a buffer.
   *
   * @param certificate The buffer containing the certificate.
   *
   * @param format The certificate format (ASN.1 or PEM).
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_use_certificate or SSL_CTX_use_certificate_ASN1.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_certificate(
      const const_buffer& certificate, file_format format,
      boost::system::error_code& ec);

  /// Use a certificate from a file.
  /**
   * This function is used to load a certificate into the context from a file.
   *
   * @param filename The name of the file containing the certificate.
   *
   * @param format The file format (ASN.1 or PEM).
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_use_certificate_file.
   */
  BOOST_ASIO_DECL void use_certificate_file(
      const std::string& filename, file_format format);

  /// Use a certificate from a file.
  /**
   * This function is used to load a certificate into the context from a file.
   *
   * @param filename The name of the file containing the certificate.
   *
   * @param format The file format (ASN.1 or PEM).
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_use_certificate_file.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_certificate_file(
      const std::string& filename, file_format format,
      boost::system::error_code& ec);

  /// Use a certificate chain from a memory buffer.
  /**
   * This function is used to load a certificate chain into the context from a
   * buffer.
   *
   * @param chain The buffer containing the certificate chain. The certificate
   * chain must use the PEM format.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_use_certificate and SSL_CTX_add_extra_chain_cert.
   */
  BOOST_ASIO_DECL void use_certificate_chain(const const_buffer& chain);

  /// Use a certificate chain from a memory buffer.
  /**
   * This function is used to load a certificate chain into the context from a
   * buffer.
   *
   * @param chain The buffer containing the certificate chain. The certificate
   * chain must use the PEM format.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_use_certificate and SSL_CTX_add_extra_chain_cert.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_certificate_chain(
      const const_buffer& chain, boost::system::error_code& ec);

  /// Use a certificate chain from a file.
  /**
   * This function is used to load a certificate chain into the context from a
   * file.
   *
   * @param filename The name of the file containing the certificate. The file
   * must use the PEM format.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_use_certificate_chain_file.
   */
  BOOST_ASIO_DECL void use_certificate_chain_file(const std::string& filename);

  /// Use a certificate chain from a file.
  /**
   * This function is used to load a certificate chain into the context from a
   * file.
   *
   * @param filename The name of the file containing the certificate. The file
   * must use the PEM format.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_use_certificate_chain_file.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_certificate_chain_file(
      const std::string& filename, boost::system::error_code& ec);

  /// Use a private key from a memory buffer.
  /**
   * This function is used to load a private key into the context from a buffer.
   *
   * @param private_key The buffer containing the private key.
   *
   * @param format The private key format (ASN.1 or PEM).
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_use_PrivateKey or SSL_CTX_use_PrivateKey_ASN1.
   */
  BOOST_ASIO_DECL void use_private_key(
      const const_buffer& private_key, file_format format);

  /// Use a private key from a memory buffer.
  /**
   * This function is used to load a private key into the context from a buffer.
   *
   * @param private_key The buffer containing the private key.
   *
   * @param format The private key format (ASN.1 or PEM).
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_use_PrivateKey or SSL_CTX_use_PrivateKey_ASN1.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_private_key(
      const const_buffer& private_key, file_format format,
      boost::system::error_code& ec);

  /// Use a private key from a file.
  /**
   * This function is used to load a private key into the context from a file.
   *
   * @param filename The name of the file containing the private key.
   *
   * @param format The file format (ASN.1 or PEM).
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_use_PrivateKey_file.
   */
  BOOST_ASIO_DECL void use_private_key_file(
      const std::string& filename, file_format format);

  /// Use a private key from a file.
  /**
   * This function is used to load a private key into the context from a file.
   *
   * @param filename The name of the file containing the private key.
   *
   * @param format The file format (ASN.1 or PEM).
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_use_PrivateKey_file.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_private_key_file(
      const std::string& filename, file_format format,
      boost::system::error_code& ec);

  /// Use an RSA private key from a memory buffer.
  /**
   * This function is used to load an RSA private key into the context from a
   * buffer.
   *
   * @param private_key The buffer containing the RSA private key.
   *
   * @param format The private key format (ASN.1 or PEM).
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_use_RSAPrivateKey or SSL_CTX_use_RSAPrivateKey_ASN1.
   */
  BOOST_ASIO_DECL void use_rsa_private_key(
      const const_buffer& private_key, file_format format);

  /// Use an RSA private key from a memory buffer.
  /**
   * This function is used to load an RSA private key into the context from a
   * buffer.
   *
   * @param private_key The buffer containing the RSA private key.
   *
   * @param format The private key format (ASN.1 or PEM).
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_use_RSAPrivateKey or SSL_CTX_use_RSAPrivateKey_ASN1.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_rsa_private_key(
      const const_buffer& private_key, file_format format,
      boost::system::error_code& ec);

  /// Use an RSA private key from a file.
  /**
   * This function is used to load an RSA private key into the context from a
   * file.
   *
   * @param filename The name of the file containing the RSA private key.
   *
   * @param format The file format (ASN.1 or PEM).
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_use_RSAPrivateKey_file.
   */
  BOOST_ASIO_DECL void use_rsa_private_key_file(
      const std::string& filename, file_format format);

  /// Use an RSA private key from a file.
  /**
   * This function is used to load an RSA private key into the context from a
   * file.
   *
   * @param filename The name of the file containing the RSA private key.
   *
   * @param format The file format (ASN.1 or PEM).
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_use_RSAPrivateKey_file.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_rsa_private_key_file(
      const std::string& filename, file_format format,
      boost::system::error_code& ec);

  /// Use the specified memory buffer to obtain the temporary Diffie-Hellman
  /// parameters.
  /**
   * This function is used to load Diffie-Hellman parameters into the context
   * from a buffer.
   *
   * @param dh The memory buffer containing the Diffie-Hellman parameters. The
   * buffer must use the PEM format.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_set_tmp_dh.
   */
  BOOST_ASIO_DECL void use_tmp_dh(const const_buffer& dh);

  /// Use the specified memory buffer to obtain the temporary Diffie-Hellman
  /// parameters.
  /**
   * This function is used to load Diffie-Hellman parameters into the context
   * from a buffer.
   *
   * @param dh The memory buffer containing the Diffie-Hellman parameters. The
   * buffer must use the PEM format.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_set_tmp_dh.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_tmp_dh(
      const const_buffer& dh, boost::system::error_code& ec);

  /// Use the specified file to obtain the temporary Diffie-Hellman parameters.
  /**
   * This function is used to load Diffie-Hellman parameters into the context
   * from a file.
   *
   * @param filename The name of the file containing the Diffie-Hellman
   * parameters. The file must use the PEM format.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_set_tmp_dh.
   */
  BOOST_ASIO_DECL void use_tmp_dh_file(const std::string& filename);

  /// Use the specified file to obtain the temporary Diffie-Hellman parameters.
  /**
   * This function is used to load Diffie-Hellman parameters into the context
   * from a file.
   *
   * @param filename The name of the file containing the Diffie-Hellman
   * parameters. The file must use the PEM format.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_set_tmp_dh.
   */
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID use_tmp_dh_file(
      const std::string& filename, boost::system::error_code& ec);

  /// Set the password callback.
  /**
   * This function is used to specify a callback function to obtain password
   * information about an encrypted key in PEM format.
   *
   * @param callback The function object to be used for obtaining the password.
   * The function signature of the handler must be:
   * @code std::string password_callback(
   *   std::size_t max_length,  // The maximum size for a password.
   *   password_purpose purpose // Whether password is for reading or writing.
   * ); @endcode
   * The return value of the callback is a string containing the password.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_CTX_set_default_passwd_cb.
   */
  template <typename PasswordCallback>
  void set_password_callback(PasswordCallback callback);

  /// Set the password callback.
  /**
   * This function is used to specify a callback function to obtain password
   * information about an encrypted key in PEM format.
   *
   * @param callback The function object to be used for obtaining the password.
   * The function signature of the handler must be:
   * @code std::string password_callback(
   *   std::size_t max_length,  // The maximum size for a password.
   *   password_purpose purpose // Whether password is for reading or writing.
   * ); @endcode
   * The return value of the callback is a string containing the password.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_CTX_set_default_passwd_cb.
   */
  template <typename PasswordCallback>
  BOOST_ASIO_SYNC_OP_VOID set_password_callback(PasswordCallback callback,
      boost::system::error_code& ec);

private:
  struct bio_cleanup;
  struct x509_cleanup;
  struct evp_pkey_cleanup;
  struct rsa_cleanup;
  struct dh_cleanup;

  // Helper function used to set a peer certificate verification callback.
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID do_set_verify_callback(
      detail::verify_callback_base* callback, boost::system::error_code& ec);

  // Callback used when the SSL implementation wants to verify a certificate.
  BOOST_ASIO_DECL static int verify_callback_function(
      int preverified, X509_STORE_CTX* ctx);

  // Helper function used to set a password callback.
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID do_set_password_callback(
      detail::password_callback_base* callback, boost::system::error_code& ec);

  // Callback used when the SSL implementation wants a password.
  BOOST_ASIO_DECL static int password_callback_function(
      char* buf, int size, int purpose, void* data);

  // Helper function to set the temporary Diffie-Hellman parameters from a BIO.
  BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID do_use_tmp_dh(
      BIO* bio, boost::system::error_code& ec);

  // Helper function to make a BIO from a memory buffer.
  BOOST_ASIO_DECL BIO* make_buffer_bio(const const_buffer& b);

  // The underlying native implementation.
  native_handle_type handle_;

  // Ensure openssl is initialised.
  boost::asio::ssl::detail::openssl_init<> init_;
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ssl/impl/context.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ssl/impl/context.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_SSL_CONTEXT_HPP

/* context.hpp
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
*/