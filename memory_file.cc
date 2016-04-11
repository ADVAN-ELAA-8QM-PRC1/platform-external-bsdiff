// Copyright 2016 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "memory_file.h"

#include "bspatch.h"

namespace bsdiff {

MemoryFile::MemoryFile(std::unique_ptr<FileInterface> file, size_t size)
    : file_(std::move(file)) {
  buffer_.reserve(size);
}

MemoryFile::~MemoryFile() {
  Close();
}

bool MemoryFile::Read(void* buf, size_t count, size_t* bytes_read) {
  return false;
}

bool MemoryFile::Write(const void* buf, size_t count, size_t* bytes_written) {
  const uint8_t* data = static_cast<const uint8_t*>(buf);
  buffer_.insert(buffer_.end(), data, data + count);
  *bytes_written = count;
  return true;
}

bool MemoryFile::Seek(off_t pos) {
  return false;
}

bool MemoryFile::Close() {
  if (!WriteAll(file_, buffer_.data(), buffer_.size()))
    return false;
  return file_->Close();
}

bool MemoryFile::GetSize(uint64_t* size) {
  *size = buffer_.size();
  return true;
}

}  // namespace bsdiff