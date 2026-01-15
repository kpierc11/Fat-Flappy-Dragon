
typedef struct
{
    Vector2 position;
    Texture2D texture;

    void (*update)();

} GameObject;

typedef struct Node
{
    GameObject data;
    struct Node *next;
} Node;

Node *insertAtBeginning(Node *head, GameObject data)
{
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    temp->data = data;

    if (temp == NULL)
    {
        printf("%s", "failed to add node");
    }

    if (head == NULL)
    {
        head = temp;
        head->next = NULL;
    }
    else
    {
        temp->next = head;
        head = temp;
    }
    return head;
}

Node *insertAtEnd(Node *head, GameObject data)
{
    // Make a new node to add to the end.
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;

    // Check if the current head in the list is null.
    // If so set the head to be the new node we just created.
    // else loop through to get to the end and add new node.
    Node *cur = head;
    if (cur == NULL)
    {
        head = temp;
    }
    else
    {
        while (cur->next != NULL)
            cur = cur->next;

        cur->next = temp;
    }

    return head;
}

void print(Node *head)
{
    Node *cur = head;
    for (cur = head; cur != NULL; cur = cur->next)
    {
        printf("%f", cur->data.position.x);
        printf("\n");
    }
}