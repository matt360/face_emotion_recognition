# Load the jpg file into a numpy array
image = face_recognition.load_image_file("obama_small.jpg")

# Find all facial features in all the faces in the image
face_landmarks_list = face_recognition.face_landmarks(image)

print("I found {} face(s) in this photograph.".format(len(face_landmarks_list)))

for face_landmarks in face_landmarks_list:
for (int face_landmarks = 0; face_landmarks < face_landmarks_list.size(); face_landmarks++)
{

    # Print the location of each facial feature in this image
    facial_features = [
        'chin',
        'left_eyebrow',
        'right_eyebrow',
        'nose_bridge',
        'nose_tip',
        'left_eye',
        'right_eye',
        'top_lip',
        'bottom_lip'
    ]
    
    for facial_feature in facial_features:
    for (int facial_feature = 0; facial_feature < facial_features.size(); ++facial_feature)
    {
        print("The {} in this face has the following points: {}".format(facial_feature, face_landmarks[facial_feature]))
        string.append("The {} in this face has the following points: {}".format(facial_feature, face_landmarks[facial_feature]))
        with open('smile.csv', 'w', newline='') as fp:
        {
            a = csv.writer(fp, delimiter='\n')
            a.writerows(string)
        }
    }
}