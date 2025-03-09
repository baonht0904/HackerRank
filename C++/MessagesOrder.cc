#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <string>
#include <random>

class Message
{
public:
    explicit Message() = default;
    Message(const std::string &text, int id);
    const std::string& get_text() const;
    friend bool operator<(const Message &lhs, const Message &rhs);
private:
    std::string text_;
    int id_;
};

class MessageFactory 
{
public:
    explicit MessageFactory() = default;
    Message create_message(const std::string &text);
private:
    int s_id_count_{0};
};

class Recipient 
{
public:
    void receive(const Message & message);
    void print_messages();
private:
    std::vector<Message> messages_;
    void fix_order();
};

class Network
{
public:
    static void send_message(const std::vector<Message> &messages, Recipient &recipient);
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    std::vector<Message> messages;
    MessageFactory message_factory;
    
    std::string text;
    while (std::getline(std::cin, text)) {
        if(text.empty())
        {
            break;
        }
        messages.emplace_back(message_factory.create_message(text));
    }

    Recipient recipient;
    Network::send_message(messages, recipient);
    recipient.print_messages();
    return 0;
}

Message::Message(const std::string &text, int id)
    : text_{text}, id_{id}
{
}

const std::string &Message::get_text() const
{
    return text_;
}

bool operator<(const Message &lhs, const Message &rhs)
{
    return lhs.id_ < rhs.id_;
}

Message MessageFactory::create_message(const std::string &text)
{
    ++s_id_count_;
    return Message(text, s_id_count_);
}

void Recipient::receive(const Message &message)
{
    messages_.push_back(message);
}

void Recipient::print_messages()
{
    this->fix_order();
    for(const auto &message: messages_) {
        std::cout << message.get_text() << std::endl;
    }
}

void Recipient::fix_order()
{
    std::sort(messages_.begin(), messages_.end());
}

void Network::send_message(const std::vector<Message> &messages, Recipient &recipient)
{
    std::vector<Message> shuffled_messages{messages};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled_messages.begin(), shuffled_messages.end(), g);

    for(const auto &message: shuffled_messages) {
        recipient.receive(message);
    }
}
