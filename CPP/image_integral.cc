#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Mat_Integral
{
    vector<vector<int>> integral;
    int width, height;
    void compute_image_integral(vector<vector<int>> mat);

  public:
    Mat_Integral(vector<vector<int>> mat);
    int get_integral(vector<int> box);
};
Mat_Integral::Mat_Integral(vector<vector<int>> mat)
{
    height = mat.size();
    if (height == 0)
        return;
    width = mat[0].size();
    if (width == 0)
        return;
    compute_image_integral(mat);
}
void Mat_Integral::compute_image_integral(vector<vector<int>> mat)
{
    integral = mat;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {

            if (i > 0)
                integral[i][j] += integral[i - 1][j];
            if (j > 0)
                integral[i][j] += integral[i][j - 1];
            if (i > 0 && j > 0)
            {
                integral[i][j] -= integral[i - 1][j - 1];
            }
        }
}
/*
* all the points in the box inclusive
* box = tl_row, tl_col, br_row, br_col
*/
int Mat_Integral::get_integral(vector<int> box)
{
    if (box[2] > height - 1 || box[3] > width - 1)
        return -1;

    int out = this->integral[box[2]][box[3]];
    // top-right
    if (box[0] > 0)
        out -= this->integral[box[0] - 1][box[3]];
    // bottom-left
    if (box[1] > 0)
        out -= this->integral[box[2]][box[1] - 1];
    if (box[0] > 0 && box[1] > 0)
        out += this->integral[box[0] - 1][box[1] - 1];
    return out;
}

vector<vector<int>> get_test_mat(int n)
{
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = i * n + j;
    return mat;
}

void print_matVec(vector<vector<int>> mat)
{
    int n = mat.size();
    if (n == 0)
        return;
    int m = mat[0].size();
    if (m == 0)
        return;
    cout << "[";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << mat[i][j];
            if (j < m - 1)
                cout << ", ";
        }
        if (i < n - 1)
            cout << "\n";
    }
    cout << "]\n";
}

int naive(vector<vector<int>> img, vector<int> bbox)
{
    int nrows = img.size();
    int ncols = img[0].size();
    if (bbox[2] > nrows - 1 || bbox[3] > ncols - 1)
        return -1;

    int out = 0;
    for (int row = bbox[0]; row < bbox[2] + 1; ++row)
        for (int col = bbox[1]; col < bbox[3] + 1; ++col)
            out += img[row][col];
    return out;
}
int main()
{
    int n = 0;
    cin >> n;
    vector<vector<int>> img = get_test_mat(n);
    Mat_Integral x(img);
    vector<int> bbox(4);
    cin >> bbox[0] >> bbox[1] >> bbox[2] >> bbox[3];
    // int result = x.get_integral(bbox);
    // print_matVec(img);
    // cout<< result <<endl;
    if (x.get_integral(bbox) == naive(img, bbox))
        cout << "PASSED\n";
    else
    {
        cout << "alg: "<< x.get_integral(bbox);
        cout << ",\t naive: "<< naive(img, bbox)<<"\n";
        cout << "FAILED!\n";
    }
    return 0;
}