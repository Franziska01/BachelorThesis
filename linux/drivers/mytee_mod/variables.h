struct shielded {
    struct shielded *next;
    struct sk_buff *skb;
    int size;

};

struct shielded *curr_shield;
