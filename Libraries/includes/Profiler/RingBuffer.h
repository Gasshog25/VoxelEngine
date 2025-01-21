template <typename Type>
class RingBuffer 
{
public:
    RingBuffer()
    {
        this->buffer = new Type[100];
        this->size = 100;
        this->fisrt = 0;
        this->last = 0;
    }

    RingBuffer(int capacity)
    {
        this->buffer = new Type[capacity];
        this->size = capacity;
        this->fisrt = 0;
        this->last = 0;
    }

    ~RingBuffer()
    {
        delete[] this->buffer;
    }


    void push(Type value)
    {
        this->buffer[this->last] = value;

        this->last = (this->last + 1) % this->size;
        if (this->last == this->fisrt) {
            this->fisrt = (this->fisrt + 1) % this->size;
        }
    };


    Type getAverage()
    {
        int count;
        if (this->last >= this->fisrt) {
            count = this->last - this->fisrt;
        } else {
            count = this->size - this->fisrt + this->last;
        }
        Type sum = Type(0);
        for (int i = this->fisrt; i != this->last; i = (i + 1) % this->size) {
            sum += this->buffer[i];
        }

        return sum / count;
    };

    Type getMin()
    {
        Type min = this->buffer[this->fisrt];
        for (int i = this->fisrt + 1; i != this->last; i = (i + 1) % this->size) {
            if (this->buffer[i] < min) {
                min = this->buffer[i];
            }
        }        

        return min;
    };

    Type getMax()
    {
        Type max = this->buffer[this->fisrt];
        for (int i = this->fisrt + 1; i != this->last; i = (i + 1) % this->size) {
            if (this->buffer[i] > max) {
                max = this->buffer[i];
            }
        }        

        return max;
    }

private:
    int size;
    int fisrt;
    int last;
    Type *buffer;
};