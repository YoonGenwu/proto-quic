// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_TEST_TOOLS_MOCK_QUIC_STREAM_FACTORY_H_
#define NET_QUIC_TEST_TOOLS_MOCK_QUIC_STREAM_FACTORY_H_

#include "base/macros.h"
#include "net/quic/chromium/quic_stream_factory.h"

namespace net {

class MockQuicStreamFactory : public QuicStreamFactory {
 public:
  MockCryptoClientStreamFactory();
  ~MockCryptoClientStreamFactory() override;

  QuicCryptoClientStream* CreateQuicCryptoClientStream(
      const QuicServerId& server_id,
      QuicChromiumClientSession* session,
      std::unique_ptr<ProofVerifyContext> proof_verify_context,
      QuicCryptoClientConfig* crypto_config) override;

  void set_handshake_mode(
      MockCryptoClientStream::HandshakeMode handshake_mode) {
    handshake_mode_ = handshake_mode;
  }

  // The caller keeps ownership of |proof_verify_details|.
  void AddProofVerifyDetails(
      const ProofVerifyDetailsChromium* proof_verify_details) {
    proof_verify_details_queue_.push(proof_verify_details);
  }

  MockCryptoClientStream* last_stream() const { return last_stream_; }

 private:
  MockCryptoClientStream::HandshakeMode handshake_mode_;
  MockCryptoClientStream* last_stream_;
  std::queue<const ProofVerifyDetailsChromium*> proof_verify_details_queue_;

  DISALLOW_COPY_AND_ASSIGN(MockCryptoClientStreamFactory);
};

}  // namespace net

#endif  // NET_QUIC_TEST_TOOLS_MOCK_CRYPTO_CLIENT_STREAM_FACTORY_H_
