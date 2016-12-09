using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public enum TypeNameFormatType
    {
        /// <summary>
        /// Empty indicates that no type or payload is associated with this record.
        /// </summary>
        Empty = 0x00,
        /// <summary>
        /// The NFC Forum well-known type follows the RTD type name format defined in the NFC Forum RTD specification.
        /// </summary>
        NfcRtd = 0x01,
        /// <summary>
        /// The media type indicates that the TYPE field contains a value that follows the media-type BNF construct defined by RFC 2046.
        /// </summary>
        Mime = 0x02,
        /// <summary>
        /// Absolute-URI indicates that the TYPE field contains a value that follows the absolute-URI BNF construct defined by RFC 3986.
        /// </summary>
        Uri = 0x03,
        /// <summary>
        /// NFC Forum external type indicates that the TYPE field contains a value that follows the type name format defined in [NFC RTD] for external type names.
        /// </summary>
        ExternalRtd = 0x04,
        /// <summary>
        /// Unknown SHOULD be used to indicate that the type of the payload is unknown. This is similar to the "application/octet-stream" media type defined by MIME.
        /// When used, the TYPE_LENGTH field MUST be zero and thus the TYPE field is omitted from the NDEF record.
        /// </summary>
        Unknown = 0x05,
        /// <summary>
        /// Unchanged MUST be used in all middle record chunks and the terminating record chunk used in chunked payloads.
        /// </summary>
        Unchanged = 0x06,
        /// <summary>
        /// Any other type name format; should be treated as unknown. 
        /// </summary>
        Reserved = 0x07
    };
}
