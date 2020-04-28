//
// Aspia Project
// Copyright (C) 2020 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef CODEC__VIDEO_ENCODER_VPX_H
#define CODEC__VIDEO_ENCODER_VPX_H

#include "base/macros_magic.h"
#include "base/memory/byte_array.h"
#include "codec/scoped_vpx_codec.h"
#include "codec/video_encoder.h"
#include "desktop/region.h"

#define VPX_CODEC_DISABLE_COMPAT 1
#include <vpx/vpx_encoder.h>
#include <vpx/vp8cx.h>

namespace codec {

class VideoEncoderVPX : public VideoEncoder
{
public:
    ~VideoEncoderVPX() = default;

    static std::unique_ptr<VideoEncoderVPX> createVP8();
    static std::unique_ptr<VideoEncoderVPX> createVP9();

    void encode(const desktop::Frame* frame, proto::VideoPacket* packet) override;

private:
    explicit VideoEncoderVPX(proto::VideoEncoding encoding);

    void createActiveMap(const desktop::Size& size);
    void createVp8Codec(const desktop::Size& size);
    void createVp9Codec(const desktop::Size& size);
    void prepareImageAndActiveMap(const desktop::Frame* frame, proto::VideoPacket* packet);
    void setActiveMap(const desktop::Rect& rect);

    desktop::Region updated_region_;
    ScopedVpxCodec codec_;

    base::ByteArray active_map_buffer_;
    vpx_active_map_t active_map_;

    // VPX image and buffer to hold the actual YUV planes.
    std::unique_ptr<vpx_image_t> image_;
    base::ByteArray image_buffer_;

    DISALLOW_COPY_AND_ASSIGN(VideoEncoderVPX);
};

} // namespace codec

#endif // CODEC___VIDEO_ENCODER_VPX_H
