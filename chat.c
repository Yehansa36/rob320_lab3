#include "util.h"
#include "messages.h"

int ctrl_c_pressed = 0;

ChattersMessage chatters;

long long get_time_us() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <discovery_server_ip> <name>\n", argv[0]);
        return 1;
    }

    const char* discovery_server_ip = argv[1];
    const char* name = argv[2];
    char* public_ip = get_public_ip();
    if (public_ip == NULL) {
        public_ip = strdup("127.0.0.1");
    }

    int discovery_fd;
    // TODO: Create a socket file descriptor for the discovery server
    //       use AF_INET for ipv4 and SOCK_STREAM for TCP
    
    // TODO: Set the socket to non-blocking mode

    struct sockaddr_in discovery_address;
    // TODO: Initialize the sockaddr_in struct for the discovery server

    int status;
    // TODO: Connect to the discovery server (use connect_until_success)

    UserMessage request_msg = {0};
    // TODO: Initialize a UserMessage struct with the request opcode

    uint8_t* request_data;
    // TODO: Encode the UserMessage struct into a byte array

    // TODO: Send the UserMessage to the discovery server (use send_until_success)

    uint8_t chatters_data[sizeof(ChattersMessage)] = {0};
    // TODO: Receive a ChattersMessage from discovery server (use recv_until_success)

    ChattersMessage* chatters_msg;
    // TODO: Decode the received ChattersMessage

    // Copy the decoded ChattersMessage to the global chatters variable
    memcpy(&chatters, chatters_msg, sizeof(ChattersMessage));

    // Print the list of chatters
    int chatter_count = print_chatters(&chatters);

    // TODO: Close the connection to the discovery server

    // If there are no chatters, return
    if (chatter_count == 0) {
        return 0;
    }

    printf("Select a chatter to send a message to: ");
    int chatter_index;
    // TODO: Read chatter index from stdin

    // If the chatter index is invalid, print an error message and return
    if (chatter_index < 0 || chatter_index >= 32) {
        fprintf(stderr, "Invalid chatter index\n");
        return 1;
    }

    int chat_fd;
    // TODO: Create a socket file descriptor for the selected chatter
    //       use AF_INET for ipv4 and SOCK_STREAM for TCP

    // TODO: Set the socket to non-blocking mode

    struct sockaddr_in chat_address;
    // TODO: Initialize the sockaddr_in struct for the selected chatter

    // TODO: Connect to the selected chatter (use connect_until_success)

    char buffer[256];
    printf("Enter message: ");
    clear_input_buffer();
    // TODO: Read message from stdin

    size_t len = strlen(buffer);
    buffer[len - 1] = '\0';

    ChatMessage chat_msg;
    // TODO: Initialize a ChatMessage struct with the user's name, message, and timestamp in microseconds

    uint8_t* chat_data;
    // TODO: Encode the ChatMessage struct into a byte array

    // TODO: Send the ChatMessage to the selected chatter (use send_until_success)

    // TODO: Close the connection to the selected chatter
    
    // Free the public IP address
    free(public_ip);
}