
#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <experimental/optional>

#include <boost/algorithm/hex.hpp>

#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <netinet/udp.h>

#include <openssl/bio.h>
#include <openssl/err.h>

#include <ngtcp2/ngtcp2.h>

using namespace std;

constexpr size_t NGTCP2_SV_SCIDLEN = 18;

void log_printf(void *user_data, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stdout, fmt, ap);
  va_end(ap);

  fprintf(stdout, "\n");
}

static int recv_client_initial(
    ngtcp2_conn *conn, const ngtcp2_cid *dcid, void *user_data) {
  printf("recv_client_initial\n");
  return 0;
}

static int recv_crypto_data(ngtcp2_conn *conn, ngtcp2_crypto_level crypto_level,
    uint64_t offset, const uint8_t *data, size_t datalen, void *user_data) {
  printf("recv_crypto_data\n");
  return 0;
}

static int encrypt(uint8_t *dest, const ngtcp2_crypto_aead *aead,
    const uint8_t *plaintext, size_t plaintextlen, const uint8_t *key,
    const uint8_t *nonce, size_t noncelen, const uint8_t *ad, size_t adlen) {
  printf("encrypt\n");
  return 0;
}

static int decrypt(uint8_t *dest, const ngtcp2_crypto_aead *aead,
    const uint8_t *ciphertext, size_t ciphertextlen, const uint8_t *key,
    const uint8_t *nonce, size_t noncelen, const uint8_t *ad, size_t adlen) {
  printf("decrypt\n");
  return 0;
}

static int hp_mask(uint8_t *dest, const ngtcp2_crypto_cipher *hp,
    const uint8_t *hp_key, const uint8_t *sample) {
  printf("hp_mask\n");
  return 0;
}

static int my_rand(ngtcp2_conn *conn, uint8_t *dest, size_t destlen,
    ngtcp2_rand_ctx ctx, void *user_data) {
  printf("my_rand\n");
  return 0;
}

static int get_new_connection_id(ngtcp2_conn *conn, ngtcp2_cid *cid,
    uint8_t *token, size_t cidlen, void *user_data) {
  printf("get_new_connection_id\n");
  return 0;
}

static int update_key(ngtcp2_conn *conn, uint8_t *rx_secret, uint8_t *tx_secret,
    uint8_t *rx_key, uint8_t *rx_iv, uint8_t *tx_key, uint8_t *tx_iv,
    const uint8_t *current_rx_secret, const uint8_t *current_tx_secret,
    size_t secretlen, void *user_data) {
  printf("update_key\n");
  return 0;
}

static string tohex(string in) {
  string out;
  boost::algorithm::hex(in, std::back_inserter(out));
  return out;
}

static string unhex(string in) {
  string out;
  boost::algorithm::unhex(in, std::back_inserter(out));
  return out;
}

int main() {
  printf("Hello, world!\n");

  ngtcp2_conn *conn;

////  std::experimental::optional<string> asdf;
////  printf("%s\n", asdf.value().c_str());
//
//  ngtcp2_path path{{4, foo},{4, bar}};
//
//  uint32_t version{NGTCP2_PROTO_VER_MAX};

  ngtcp2_conn_callbacks callbacks{};
  callbacks.recv_client_initial = recv_client_initial;
  callbacks.recv_crypto_data = recv_crypto_data;
  callbacks.encrypt = encrypt;
  callbacks.decrypt = decrypt;
  callbacks.hp_mask = hp_mask;
  callbacks.rand = my_rand;
  callbacks.get_new_connection_id = get_new_connection_id;
  callbacks.update_key = update_key;

  ngtcp2_settings settings;
  ngtcp2_settings_default(&settings);
  settings.log_printf = log_printf;

  //  char buf[1200];
    string sample(unhex("C3513034360590630E844F22F4F600000001999126C1DF644458510D2FD5400120A10100A00101A552454A000700000053544B0038000000534E4F006C00000050524F46B300000053434647460100005252454A4A0100005354544C52010000435254FF65010000E14266783627FFAEA6E6232194F87D0550E0F98846DC64C4044E7458B36AEE55E71C23893BF05D504937C5C9166B951BED61335A8877391052A9C3F4B565F37F2A175A3D0EF1C9547F9B291CCB10D600A126CD688263B5F4C9288DDC9EFE69E182B65B0641D9032C9E881D343045022100FC8AFEEFCDD7CF9B7BE039D06BCAB4CC8EF70EE9F92C3389E6412719905F8250022048D236AE4710C22B5914688649F9B5C2379303764F283D8529D5C3F85F4D18E853434647070000004145414408000000534349441800000050444D441C000000505542533F0000004B455853430000004F4249544B000000455850595300000041455347434332305FDE61E923C34C243CF9B4D9B6E3B516434849442000007980F55D1D41444811E7B78DD63F73050FD305F3A376154D019EC1E0F5DE5710433235353030303030303030403C7F5E000000000D0000003E5602000000000002BDAAB806CD8CF1A1026032CB92A0414DDF0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    uint8_t buf[65536];
    auto nread = sample.size();
    memcpy(buf, sample.data(), nread);

//  ngtcp2_conn_set_initial_crypto_ctx(conn, ctx)
  uint32_t version{NGTCP2_PROTO_VER_MAX}; // 0xff00001b
  const uint8_t *dcid, *scid;
  size_t dcidlen, scidlen;

  {
    /* 1 byte (Header Form, Fixed Bit, Long Packet Type, Type-Specific bits)
     * 4 bytes Version
     * 1 byte DCID Length
     * 1 byte SCID Length
     */

    // C3 51303436 05 90 63

    auto rv = ngtcp2_pkt_decode_version_cid(&version, &dcid, &dcidlen, &scid, &scidlen, buf, nread, NGTCP2_SV_SCIDLEN);
    printf("ngtcp2_pkt_decode_version_cid %d\n", rv);
    if (rv != 0)
      printf("ngtcp2_pkt_decode_version_cid %s\n", ngtcp2_strerror(rv));
  }

  ngtcp2_pkt_hd hd;

  {

    /**
     * @function
     *
     * `ngtcp2_accept` is used by server implementation, and decides
     * whether packet |pkt| of length |pktlen| is acceptable for initial
     * packet from client.
     *
     * If it is acceptable, it returns 0.  If it is not acceptable, and
     * Version Negotiation packet is required to send, it returns 1.
     * Otherwise, it returns -1.
     *
     * If |dest| is not NULL, and the return value is 0 or 1, the decoded
     * packet header is stored to the object pointed by |dest|.
     */
    auto rv = ngtcp2_accept(&hd, buf, nread);
    printf("ngtcp2_accept %d\n", rv);
    if (rv == -1) {
      printf("ngtcp2_accept %s\n", ngtcp2_strerror(rv));
    }

  }
//  typedef struct ngtcp2_addr {
//    /* addrlen is the length of addr. */
//    size_t addrlen;
//    /* addr points to the buffer which contains endpoint address.  It is
//       opaque to the ngtcp2 library. */
//    uint8_t *addr;
//    /* user_data is an arbitrary data and opaque to the library. */
//    void *user_data;
//  } ngtcp2_addr;

//  typedef struct ngtcp2_path {
//    /* local is the address of local endpoint. */
//    ngtcp2_addr local;
//    /* remote is the address of remote endpoint. */
//    ngtcp2_addr remote;
//  } ngtcp2_path;

  sockaddr_in local{1};
  sockaddr_in remote{2};

  auto path = ngtcp2_path {
    { sizeof(local), (uint8_t*) &local },
    { sizeof(remote), (uint8_t*) &remote },
  };

  {

//    if (auto rv = ngtcp2_conn_server_new(&conn_, dcid, &scid_, &path, version,
//                                         &callbacks, &settings, nullptr, this);
//        rv != 0) {
//      std::cerr << "ngtcp2_conn_server_new: " << ngtcp2_strerror(rv) << std::endl;
//      return -1;
//    }
//    if (h->init(ep, &su.sa, addrlen, &hd.scid, &hd.dcid, pocid, hd.token,
//                hd.tokenlen, hd.version) != 0) {


    if (ngtcp2_conn_server_new(&conn, &hd.dcid, &hd.scid, &path, version, &callbacks, &settings, 0, 0)!=0)
      printf("Oof!");
    }

//  printf("%s\n", hex(string(buf, sizeof(buf))).c_str());
//  printf("%s\n", unhex(hex(string(buf, sizeof(buf)))).c_str());

  {
    auto rv = ngtcp2_conn_read_pkt(conn, &path, buf, nread, 0);
    printf("ngtcp2_conn_read_pkt %s\n", ngtcp2_strerror(rv));
  }

  return 0;
}
