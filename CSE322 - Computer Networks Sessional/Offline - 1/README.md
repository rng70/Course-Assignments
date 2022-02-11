# Socket Programming

---

### Core Functionalities

1. Each student has a specific IP address. A student can Login (i.e., connect to the server) with his/her
student ID. If the student ID is already logged in from another IP address, new login is denied by the
server and the connection is immediately terminated with proper message. So, each student is mapped
to a single IP address at any instance. When a student gets connected for the first time, the server
creates a directory with the student ID as directory name. All the files uploaded by this student will be
stored in this directory.
2. While connected, a student can:
  1. Look up the list of all the students who were connected at least once to the server. The
    students who are currently online should be distinguishable in the list.
  2. Look up the list of all the files (both private and public) uploaded by him/her and download
    any of these files. Private and public files should be distinguishable in the list.
  3. Look up the public files of a specific student and download any of these files.
  4. Request for a file. This request (short file description and request id) will be broadcasted
    to all the connected students.
  5. View all the unread messages.
  6. Upload a file.
  7. The file can be either public or private and it will be specified by the uploader.
  8. If the file is uploaded in response to a request, it must be public and the uploader
    will provide valid request Id.
  9. When a requested file has been uploaded, the server sends a message to the person who
    requested for that file. Multiple students can upload the same requested file and the server
    will send as many messages.

### Implementation Details

1.   Configurable parameters for the server:
     1.   MAX_BUFFER_SIZE
     2.   MIN_CHUNK_SIZE
     3.   MAX_CHUNK_SIZE
2.   While uploading a file, sender first sends the filename and file size to the server. The server
     checks the total size of all chunks stored in the buffer plus the new file size. If it overflows the
     maximum size, the server does not allow the transmission. Otherwise, the server randomly
     3.4.5.6.7.generates Chunk Size (between MIN and MAX CHUNK SIZE) and sends a confirmation
     message to the sender with the Chunk Size and a fileID, which is used as the file identifier for
     the rest of the file transmission. So, you need to maintain a lin k between the fileID and
     fileName and other info inside the server.
     Now the sender splits the file into chunks depending on the Chunk Size. Let, a file size is 1235
     KB and the server allows that client maximum 100 KB for each chunk. So, client splits the file
     into 13 chunks (first 12 chunks with 100KB, the last chunk with 35 KB) and sends all the
     chunks sequentially.
     After receiving each chunk, the server sends an acknowledgement. The sender sends the next
     chunk only after receiving the acknowledgement. If the sender does not receive any
     acknowledgement within 30 seconds, it sends a timeout message to the server and terminates
     the transmission. After receiving the timeout message, the server should delete the chunk files
     for the corresponding fileID.
     When the sender receives acknowledgement for the last chunk, it sends a completion message
     to the server. Then the server checks the file size by adding all the chunk sizes. If size of all
     chunks matches the initial file size mentioned by the sender, the server is done with the sender
     and sends a success message. Else, the server sends an error message indicating failure and
     deletes all the chunks.
     A student goes offline if he/she logs out or gets disconnected. If the sender goes offline in the
     middle of a file transmission (between sender and server), discard the files from server.
     Unlike upload, the server does not carefully monitor download of a file. It sends the file with
     the chunk size of MAX_CHUNK_SIZE and does not wait for the receiver’s acknowledgement.
     When the download is completed the receiver gets a completion message from the server.