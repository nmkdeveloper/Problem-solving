#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
typedef set<int> si;
typedef set<ll> sll;
typedef priority_queue<int> max_heap_i;
typedef priority_queue<int, vi, greater<int>> min_heap_i;
typedef priority_queue<ll> max_heap_ll;
typedef priority_queue<ll, vll, greater<ll>> min_heap_ll;

#define FOR(a, b, c) for (int a = (b); a <= (c); a++)
#define FORD(a, b, c) for (int a = (b); a >= (c); a--)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define REPD(i, n) for (int i = (n) - 1; i >= 0; i--)
#define endl '\n'
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

#define BIT(n) (1 << (n))
#define SET(k, n) ((n) | BIT(k))
#define CLEAR(k, n) ((n) & ~BIT(k))
#define TOGGLE(k, n) ((n) ^ BIT(k))
#define CHECK(k, n) (!!((n) & BIT(k)))
#define MSB(x) ((x) == 0 ? -1 : 63 - __builtin_clzll(x))

#define debug(x) clog << #x << " = " << (x) << endl

const int MAXARR = 1e7 + 15;
const int INF = 1e9 + 7;
const ll INF64 = 2e18 + 7;
const int MOD = 1e9 + 7;

void fixIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void File(const string &fileName = "")
{
    if (fopen((fileName + ".INP").c_str(), "r"))
    {
        freopen((fileName + ".INP").c_str(), "r", stdin);
        freopen((fileName + ".OUT").c_str(), "w", stdout);
    }
}

void Read()
{

}

void Solve()
{

}

int main()
{
    fixIO();
    File("");
    Read();
    Solve();
    return 0;
}

/*
 * Code by github/nmkdeveloper.
 * 
 * "As a friend!" repeated Mr. Knightley. "Emma, that I fear is a word - No, I have no wish. Stay - yes, why should I hesitate? I have gone too far already for concealment. Emma, I accept your offer; extraordinary as it may seem, I accept it, and refer myself to you as a friend. Tell me, then, have I no chance of ever succeeding?"
 * He stopped in his earnestness to look the question, and the expression of his eyes overpowered her.
 * "My dearest Emma," said he, "for dearest you will always be, whatever the event of this hour's conversation, my dearest, most beloved Emma - tell me at once. Say 'No' if it is to be said."
 * She could really say nothing.
 * "You are silent," he cried, with great animation; "absolutely silent! at present I ask no more."
 * Emma was almost ready to sink under the agitation of this moment. The dread of being awakened from the happiest dream was perhaps the most prominent feeling.
 * "I cannot make speeches, Emma," he soon resumed, and in a tone of such sincere, decided, intelligible tenderness as was tolerably convincing. "If I loved you less, I might be able to talk about it more. But you know what I am. You hear nothing but truth from me. I have blamed you, and lectured you, and you have borne it as no other woman in England would have borne it. Bear with the truths I would tell you now, dearest Emma, as well as you have borne with them. The manner, perhaps, may have as little to recommend them. God knows, I have been a very indifferent lover. But you understand me. Yes, you see, you understand my feelings - and will return them if you can. At present, I ask only to hear, once to hear your voice."
 * While he spoke, Emma's mind was most busy, and, with all the wonderful velocity of thought, had been able - and yet without losing a word - to catch and comprehend the exact truth of the whole; to see that Harriet's hopes had been entirely groundless, a mistake, a delusion, as complete a delusion as any of her own - that Harriet was nothing; that she was everything herself; that what she had been saying relative to Harriet had been all taken as the language of her own feelings; and that her agitation, her doubts, her reluctance, her discouragement, had been all received as discouragement from herself.
 * "Mr. Knightley," said Emma, "I am your own Emma, by word and hand."
 * - Austen, Jane. Emma. 1815. Ch. 49. Project Gutenberg, www.gutenberg.org/ebooks/158. Accessed 12 Oct. 2026. -
 *
 */