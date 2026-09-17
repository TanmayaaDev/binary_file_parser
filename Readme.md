# Custom C Binary File Parser & Serializer (`binary-file-parser`)

A low-level C library and parsing engine for custom binary file serialization (`.vdb` format) featuring packed header validation, magic bytes identification, and array checksum integrity checking.

## 📌 Architectural Features
- **16-Byte Packed Header:** Structured metadata storage enforcing byte alignment via `__attribute__((packed))`.
- **Magic Bytes Signature:** Format identification using hexadecimal signatures (`0x56444231`).
- **Dynamic Payload Allocation:** Deserializes contiguous dynamic array streams directly into heap memory.
- **Checksum Integrity:** Additive byte validation layer preventing corrupt payload reads.

## 🚀 Quickstart
```bash
# Build and run serializer test
make clean && make && ./binary_parser