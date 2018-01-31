import face_recognition

image = face_recognition.load_image_file("6.jpg")
face_locations = face_recognition.face_locations(image)
print("I found {} face(s) in this photograph.".format(len(face_locations)))
