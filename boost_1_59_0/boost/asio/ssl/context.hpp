//
// ssl/context.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

  // Translate an SSL error into an error code.
  BOOST_ASIO_DECL static boost::system::error_code translate_error(long error);

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